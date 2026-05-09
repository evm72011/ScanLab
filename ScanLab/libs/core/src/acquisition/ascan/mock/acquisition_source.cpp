#include "scanlab/acquisition/ascan/acquisition_source.h"

#include <UTDriverOEMPA.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <expected>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

namespace sd = scanlab::device;

namespace scanlab::acquisition::ascan
{
namespace
{

struct MockState
{
    std::atomic<bool> running{false};
    std::atomic<bool> stopRequested{false};
    std::thread worker;
};

std::mutex g_statesMutex;
std::unordered_map<const AcquisitionSource *, std::unique_ptr<MockState>>
    g_states;

MockState *findState(const AcquisitionSource *source)
{
    std::lock_guard lock(g_statesMutex);
    const auto it = g_states.find(source);
    return it != g_states.end() ? it->second.get() : nullptr;
}

MockState &ensureState(const AcquisitionSource *source)
{
    std::lock_guard lock(g_statesMutex);
    auto &state = g_states[source];
    if (!state)
    {
        state = std::make_unique<MockState>();
    }
    return *state;
}

std::unique_ptr<MockState> extractState(const AcquisitionSource *source)
{
    std::lock_guard lock(g_statesMutex);
    const auto it = g_states.find(source);
    if (it == g_states.end())
    {
        return nullptr;
    }

    auto state = std::move(it->second);
    g_states.erase(it);
    return state;
}

double gaussian(double x, double center, double width)
{
    const double z = (x - center) / width;
    return std::exp(-0.5 * z * z);
}

double dampedSin(double x,
                 double start,
                 double amplitude,
                 double decay,
                 double frequency)
{
    if (x < start)
    {
        return 0.0;
    }

    const double t = x - start;
    return amplitude * std::exp(-t / decay) *
           std::sin(2.0 * 3.14159265358979323846 * frequency * t);
}

std::vector<std::int16_t> generateSignal(std::size_t sampleCount, int cycle)
{
    std::vector<std::int16_t> signal(sampleCount, 0);

    std::mt19937 rng(static_cast<std::uint32_t>(0x9E3779B9u + cycle * 17));
    std::normal_distribution<double> noise(0.0, 110.0);

    const double drift = std::sin(static_cast<double>(cycle) * 0.05);
    const double shift1 = 2.0 * std::sin(static_cast<double>(cycle) * 0.030);
    const double shift2 =
        3.0 * std::sin(static_cast<double>(cycle) * 0.022 + 1.4);
    const double shift3 =
        2.0 * std::sin(static_cast<double>(cycle) * 0.017 + 2.2);

    for (std::size_t i = 0; i < sampleCount; ++i)
    {
        const double x = static_cast<double>(i);

        double y = 0.0;

        // Слабый фон около нуля.
        y += 80.0 *
             std::sin(2.0 * 3.14159265358979323846 * 0.11 * x + cycle * 0.02);
        y += 55.0 * std::sin(2.0 * 3.14159265358979323846 * 0.073 * x + 0.8);

        // Левый сильный отрицательный провал и восстановление.
        y += -20500.0 * gaussian(x, 14.0 + shift1, 1.8);
        y += -7200.0 * gaussian(x, 18.0 + shift1, 5.5);
        y += dampedSin(x, 21.0 + shift1, 2600.0, 18.0, 0.060);

        // Раннее эхо слева: большой положительный пик и хвост.
        y += 14200.0 * gaussian(x, 53.0 + shift1, 1.7);
        y += dampedSin(x, 56.0 + shift1, 4600.0, 18.0, 0.072);

        // Небольшие колебания перед основной серединой.
        y += dampedSin(x, 82.0 + shift1, 1200.0, 28.0, 0.078);

        // Основное центральное эхо: глубокий отрицательный + два высоких положительных.
        y += -13200.0 * gaussian(x, 246.0 + shift2, 1.6);
        y += 8800.0 * gaussian(x, 243.0 + shift2, 1.2);
        y += 9200.0 * gaussian(x, 250.0 + shift2, 1.3);
        y += dampedSin(x, 252.0 + shift2, 3000.0, 11.0, 0.082);

        // Позднее правое слабое эхо.
        y += 4200.0 * gaussian(x, 468.0 + shift3, 1.3);
        y += -6200.0 * gaussian(x, 472.0 + shift3, 1.2);
        y += 3600.0 * gaussian(x, 476.0 + shift3, 1.2);
        y += dampedSin(x, 478.0 + shift3, 1400.0, 8.0, 0.090);

        // Небольшой baseline drift.
        y += 120.0 * drift;

        // Небольшой шум.
        y += noise(rng);

        y = std::clamp(y, -32768.0, 32767.0);
        signal[i] = static_cast<std::int16_t>(y);
    }

    return signal;
}

std::vector<std::uint8_t> packSignal(const std::vector<std::int16_t> &signal)
{
    std::vector<std::uint8_t> data(signal.size() * sizeof(std::int16_t));
    if (!signal.empty())
    {
        std::memcpy(data.data(), signal.data(), data.size());
    }
    return data;
}

} // namespace

AcquisitionSource::AcquisitionSource(sd::Device &device)
    : device_(device), control_(device)
{
}

void AcquisitionSource::setCycleFilter(int cycle)
{
    std::lock_guard lock(mutex_);
    cycleFilter_ = cycle;
}

AcquisitionSource::~AcquisitionSource()
{
    stop();
}

void AcquisitionSource::setFrameHandler(FrameHandler handler)
{
    std::lock_guard lock(mutex_);
    handler_ = std::move(handler);
}

std::expected<void, AcquisitionError> AcquisitionSource::start()
{
    auto &state = ensureState(this);

    bool expected = false;
    if (!state.running.compare_exchange_strong(expected, true))
    {
        return {};
    }

    state.stopRequested.store(false);

    if (state.worker.joinable())
    {
        state.worker.join();
    }

    state.worker = std::thread([this, &state]() {
        constexpr std::size_t sampleCount = 512;
        constexpr auto period = std::chrono::milliseconds(20);

        int cycle = 0;

        while (!state.stopRequested.load())
        {
            FrameHandler localHandler;
            {
                std::lock_guard lock(mutex_);
                localHandler = handler_;
            }

            if (localHandler)
            {
                const auto signal = generateSignal(sampleCount, cycle);

                RawFrame frame{.dataSize =
                                   static_cast<int>(sizeof(std::int16_t)),
                               .dataCount = static_cast<int>(sampleCount),
                               .cycle = cycle,
                               .bitSize = static_cast<int>(e16Bits),
                               .sign = true,
                               .data = packSignal(signal)};

                localHandler(std::move(frame));
            }

            ++cycle;
            std::this_thread::sleep_for(period);
        }

        state.running.store(false);
    });

    return {};
}

void AcquisitionSource::stop()
{
    auto state = extractState(this);
    if (!state)
    {
        return;
    }

    state->stopRequested.store(true);

    if (state->worker.joinable())
    {
        state->worker.join();
    }

    state->running.store(false);
}

bool AcquisitionSource::isRunning() const
{
    const auto *state = findState(this);
    return state && state->running.load();
}

void AcquisitionSource::registerCallbacks()
{
}

void AcquisitionSource::unregisterCallbacks()
{
}

UINT WINAPI AcquisitionSource::callback(void *,
                                        structAcqInfoEx &,
                                        const CStream_0x0001 *,
                                        const CSubStreamAscan_0x0103 *,
                                        const void *,
                                        const void *,
                                        const void *)
{
    return 0;
}

void AcquisitionSource::handle(const CSubStreamAscan_0x0103 *, const void *)
{
}

} // namespace scanlab::acquisition::ascan