#include "scanlab/hardware/a_scan_acquisition.h"

#include <UTDriverOEMPA.h>

#include <algorithm>
#include <cstdint>
#include <limits>
#include <mutex>
#include <utility>
#include <iostream>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace scanlab::hardware {

class AScanAcquisition::Impl
{
public:
    Device* device = nullptr;
    SamplesHandler handler;
    int targetSampleCount = 512;
    bool running = false;
    mutable std::mutex mutex;

    CHWDeviceOEMPA* nativeDevice()
    {
        return device ? device->get() : nullptr;
    }

    const CHWDeviceOEMPA* nativeDevice() const
    {
        return device ? device->get() : nullptr;
    }

    void registerCallbacks()
    {
        auto* native = nativeDevice();
        if (!native) {
            return;
        }

        native->SetAcquisitionParameter(this);
        native->SetAcquisitionAscan_0x00010103(&Impl::callbackV1);
        native->SetAcquisitionAscan_0x00020203(nullptr);
    }

    void unregisterCallbacks()
    {
        auto* native = nativeDevice();
        if (!native) {
            return;
        }

        native->SetAcquisitionAscan_0x00010103(nullptr);
        native->SetAcquisitionAscan_0x00020203(nullptr);
        native->SetAcquisitionParameter(nullptr);
    }

    static UINT WINAPI callbackV1(
        void* pAcquisitionParameter,
        structAcqInfoEx&,
        const CStream_0x0001*,
        const CSubStreamAscan_0x0103* pAscanHeader,
        const void* pBufferMax,
        const void*,
        const void*)
    {
        auto* self = static_cast<Impl*>(pAcquisitionParameter);
        if (!self || !pAscanHeader || !pBufferMax) {
            return 0;
        }

        self->handleBuffer(
            static_cast<int>(pAscanHeader->dataSize),
            static_cast<int>(pAscanHeader->dataCount),
            pBufferMax);

        return 0;
    }

    static UINT WINAPI callbackV2(
        void*,
        const CStream_0x0002*,
        const CSubStreamAscan_0x0203*,
        const void*,
        const void*,
        const void*)
    {
        return 0;
    }

    void handleBuffer(int dataSize, int dataCount, const void* buffer)
    {
        SamplesHandler localHandler;
        int localTargetSampleCount = 0;
        bool localRunning = false;

        {
            std::lock_guard<std::mutex> lock(mutex);
            localHandler = handler;
            localTargetSampleCount = targetSampleCount;
            localRunning = running;
        }

        if (!localRunning || !localHandler) {
            return;
        }

        Samples samples = convertBufferToSamples(buffer, dataSize, dataCount);
        if (samples.empty()) {
            return;
        }

        if (localTargetSampleCount > 1 && static_cast<int>(samples.size()) != localTargetSampleCount) {
            samples = resample(samples, localTargetSampleCount);
        }

        localHandler(std::move(samples));
    }

    static Samples convertBufferToSamples(const void* buffer, int dataSize, int dataCount)
    {
        Samples result;

        if (!buffer || dataSize <= 0 || dataCount <= 0) {
            return result;
        }

        result.reserve(static_cast<std::size_t>(dataCount));

        switch (dataSize) {
        case 1: {
            const auto* src = static_cast<const std::uint8_t*>(buffer);
            for (int i = 0; i < dataCount; ++i) {
                result.push_back(static_cast<float>(src[i]) / 255.0f);
            }
            break;
        }

        case 2: {
            const auto* src = static_cast<const std::uint16_t*>(buffer);
            for (int i = 0; i < dataCount; ++i) {
                result.push_back(static_cast<float>(src[i]) / 65535.0f);
            }
            break;
        }

        case 4: {
            const auto* src = static_cast<const std::uint32_t*>(buffer);
            constexpr double denom =
                static_cast<double>(std::numeric_limits<std::uint32_t>::max());

            for (int i = 0; i < dataCount; ++i) {
                result.push_back(static_cast<float>(static_cast<double>(src[i]) / denom));
            }
            break;
        }

        default:
            break;
        }

        return result;
    }

    static Samples resample(const Samples& input, int targetCount)
    {
        if (targetCount <= 1 || input.empty()) {
            return input;
        }

        if (static_cast<int>(input.size()) == targetCount) {
            return input;
        }

        Samples output(static_cast<std::size_t>(targetCount));

        if (input.size() == 1) {
            std::fill(output.begin(), output.end(), input.front());
            return output;
        }

        const int srcLast = static_cast<int>(input.size()) - 1;
        const int dstLast = targetCount - 1;

        for (int i = 0; i < targetCount; ++i) {
            const double pos =
                static_cast<double>(i) * static_cast<double>(srcLast) / static_cast<double>(dstLast);

            const int left = static_cast<int>(pos);
            const int right = std::min(left + 1, srcLast);
            const double t = pos - static_cast<double>(left);

            output[static_cast<std::size_t>(i)] =
                static_cast<float>(input[static_cast<std::size_t>(left)] * (1.0 - t) +
                                   input[static_cast<std::size_t>(right)] * t);
        }

        return output;
    }
};

AScanAcquisition::AScanAcquisition()
    : impl_(std::make_unique<Impl>())
{
}

AScanAcquisition::~AScanAcquisition()
{
    stop();
}

AScanAcquisition::AScanAcquisition(AScanAcquisition&&) noexcept = default;
AScanAcquisition& AScanAcquisition::operator=(AScanAcquisition&&) noexcept = default;

void AScanAcquisition::setDevice(Device* device)
{
    stop();
    impl_->device = device;
}

Device* AScanAcquisition::device()
{
    return impl_->device;
}

const Device* AScanAcquisition::device() const
{
    return impl_->device;
}

void AScanAcquisition::setSamplesHandler(SamplesHandler handler)
{
    std::lock_guard<std::mutex> lock(impl_->mutex);
    impl_->handler = std::move(handler);
}

void AScanAcquisition::setTargetSampleCount(int value)
{
    if (value < 2) {
        return;
    }

    std::lock_guard<std::mutex> lock(impl_->mutex);
    impl_->targetSampleCount = value;
}

bool AScanAcquisition::start()
{
    auto* native = impl_->nativeDevice();
    if (!native) {
        std::cout << "AScan: no native device\n" << std::boolalpha;
        return false;
    }

    std::cout << "AScan: registering callbacks\n";
    impl_->registerCallbacks();

    if (!native->LockDevice()) {
        std::cout << "AScan: LockDevice failed\n";
        impl_->unregisterCallbacks();
        return false;
    }

    const bool ok = native->UnlockDevice(eAcqOn);
    std::cout << "AScan: UnlockDevice(eAcqOn)=" << ok << '\n';

    if (!ok) {
        impl_->unregisterCallbacks();
        return false;
    }

    {
        std::lock_guard<std::mutex> lock(impl_->mutex);
        impl_->running = true;
    }

    std::cout << "AScan: started\n";
    return true;
}

void AScanAcquisition::stop()
{
    auto* native = impl_->nativeDevice();

    {
        std::lock_guard<std::mutex> lock(impl_->mutex);
        impl_->running = false;
    }

    if (native && native->LockDevice()) {
        native->UnlockDevice(eAcqOff);
    }

    impl_->unregisterCallbacks();
}

bool AScanAcquisition::isRunning() const
{
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return impl_->running;
}

} // namespace scanlab::hardware