#include "scanlab/hardware/a_scan_acquisition.h"

#include <UTDriverOEMPA.h>

#include <algorithm>
#include <cstdint>
#include <limits>
#include <mutex>
#include <utility>
#include <vector>

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
            static_cast<int>(pAscanHeader->cycle),
            static_cast<int>(pAscanHeader->bitSize),
            pAscanHeader->sign != 0,
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

    void handleBuffer(
        int dataSize,
        int dataCount,
        int cycle,
        int bitSize,
        bool sign,
        const void* buffer)
    {
        SamplesHandler localHandler;
        bool localRunning = false;
        int targetCount = 0;

        {
            std::lock_guard<std::mutex> lock(mutex);
            localHandler = handler;
            localRunning = running;
            targetCount = targetSampleCount;
        }

        if (!localRunning || !localHandler) {
            return;
        }

        std::vector<float> samples =
            convertBufferToSamples(buffer, dataSize, dataCount, bitSize, sign);

        if (samples.empty()) {
            return;
        }

        samples = resample(samples, targetCount);

        AScanAcquisition::Frame frame;
        frame.samples = std::move(samples);
        frame.cycle = cycle;
        frame.dataSize = dataSize;
        frame.bitSize = bitSize;
        frame.sign = sign;

        localHandler(std::move(frame));
    }

    static int effectiveBitWidth(int bitSize, int dataSize)
    {
        // OEMPA sample: 12-bit может реально лежать в 16 битах,
        // а при dataSize == 4 это может быть 27-bit контейнер.
        switch (bitSize) {
        case eLog8Bits:
        case e8Bits:
            return 8;

        case e12Bits:
            if (dataSize == 4) {
                return 27;
            }
            if (dataSize == 2) {
                // минимально корректно для отображения: считать как 16-bit контейнер
                return 16;
            }
            return 12;

        case e16Bits:
            if (dataSize == 2) {
                return 16;
            }
            return 16;

#ifdef MC2_FULL_DYNAMIC
        case e30Bits:
            return 30;
#endif

        default:
            return dataSize * 8;
        }
    }

    static float normalizeSigned(std::int64_t value, int bits)
    {
        if (bits <= 1) {
            return 0.0f;
        }

        const std::int64_t maxPositive = (std::int64_t{1} << (bits - 1)) - 1;
        if (maxPositive <= 0) {
            return 0.0f;
        }

        double v = static_cast<double>(value) / static_cast<double>(maxPositive);
        v = std::clamp(v, -1.0, 1.0);
        return static_cast<float>(v);
    }

    static float normalizeUnsigned(std::uint64_t value, int bits)
    {
        if (bits <= 0) {
            return 0.0f;
        }

        const std::uint64_t maxValue =
            (bits >= 64) ? std::numeric_limits<std::uint64_t>::max()
                         : ((std::uint64_t{1} << bits) - 1);

        if (maxValue == 0) {
            return 0.0f;
        }

        double v = static_cast<double>(value) / static_cast<double>(maxValue);
        v = std::clamp(v, 0.0, 1.0);
        return static_cast<float>(v);
    }

    static std::vector<float> convertBufferToSamples(
        const void* buffer,
        int dataSize,
        int dataCount,
        int bitSize,
        bool sign)
    {
        std::vector<float> result;

        if (!buffer || dataSize <= 0 || dataCount <= 0) {
            return result;
        }

        result.reserve(static_cast<std::size_t>(dataCount));

        const int bits = effectiveBitWidth(bitSize, dataSize);

        switch (dataSize) {
        case 1: {
            if (sign) {
                const auto* src = static_cast<const std::int8_t*>(buffer);
                for (int i = 0; i < dataCount; ++i) {
                    result.push_back(normalizeSigned(src[i], 8));
                }
            } else {
                const auto* src = static_cast<const std::uint8_t*>(buffer);
                for (int i = 0; i < dataCount; ++i) {
                    result.push_back(normalizeUnsigned(src[i], 8));
                }
            }
            break;
        }

        case 2: {
            if (sign) {
                const auto* src = static_cast<const std::int16_t*>(buffer);
                for (int i = 0; i < dataCount; ++i) {
                    result.push_back(normalizeSigned(src[i], bits));
                }
            } else {
                const auto* src = static_cast<const std::uint16_t*>(buffer);
                for (int i = 0; i < dataCount; ++i) {
                    result.push_back(normalizeUnsigned(src[i], bits));
                }
            }
            break;
        }

        case 4: {
            if (sign) {
                const auto* src = static_cast<const std::int32_t*>(buffer);
                for (int i = 0; i < dataCount; ++i) {
                    result.push_back(normalizeSigned(src[i], bits));
                }
            } else {
                const auto* src = static_cast<const std::uint32_t*>(buffer);
                for (int i = 0; i < dataCount; ++i) {
                    result.push_back(normalizeUnsigned(src[i], bits));
                }
            }
            break;
        }

        default:
            break;
        }

        return result;
    }

    static std::vector<float> resample(const std::vector<float>& input, int targetCount)
    {
        if (targetCount <= 1 || input.empty()) {
            return input;
        }

        if (static_cast<int>(input.size()) == targetCount) {
            return input;
        }

        std::vector<float> output(static_cast<std::size_t>(targetCount));

        if (input.size() == 1) {
            std::fill(output.begin(), output.end(), input.front());
            return output;
        }

        const int srcLast = static_cast<int>(input.size()) - 1;
        const int dstLast = targetCount - 1;

        for (int i = 0; i < targetCount; ++i) {
            const double pos =
                static_cast<double>(i) * static_cast<double>(srcLast) /
                static_cast<double>(dstLast);

            const int left = static_cast<int>(pos);
            const int right = std::min(left + 1, srcLast);
            const double t = pos - static_cast<double>(left);

            output[static_cast<std::size_t>(i)] =
                static_cast<float>(
                    input[static_cast<std::size_t>(left)] * (1.0 - t) +
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
        return false;
    }

    impl_->registerCallbacks();

    if (!native->LockDevice()) {
        impl_->unregisterCallbacks();
        return false;
    }

    const bool ok = native->UnlockDevice(eAcqOn);
    if (!ok) {
        impl_->unregisterCallbacks();
        return false;
    }

    {
        std::lock_guard<std::mutex> lock(impl_->mutex);
        impl_->running = true;
    }

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