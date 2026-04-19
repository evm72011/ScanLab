#include "scanlab/acquisition/ascan/acquisition_source.h"

#include <UTDriverOEMPA.h>

#include <cstring>
#include <utility>

namespace sd = scanlab::device;

namespace scanlab::acquisition::ascan {

AcquisitionSource::AcquisitionSource(sd::Device& device)
    : device_(device)
    , control_(device)
{
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
    return control_.start(
        [this]() { registerCallbacks(); },
        [this]() { unregisterCallbacks(); });
}

void AcquisitionSource::stop()
{
    control_.stop([this]() { unregisterCallbacks(); });
}

bool AcquisitionSource::isRunning() const
{
    return control_.isRunning();
}

void AcquisitionSource::registerCallbacks()
{
    auto* hw = device_.get();
    if (!hw) {
        return;
    }

    hw->SetAcquisitionParameter(this);
    hw->SetAcquisitionAscan_0x00010103(&AcquisitionSource::callback);
    hw->SetAcquisitionAscan_0x00020203(nullptr);
}

void AcquisitionSource::unregisterCallbacks()
{
    auto* hw = device_.get();
    if (!hw) {
        return;
    }

    hw->SetAcquisitionAscan_0x00010103(nullptr);
    hw->SetAcquisitionAscan_0x00020203(nullptr);
    hw->SetAcquisitionParameter(nullptr);
}

UINT WINAPI AcquisitionSource::callback(
    void* p,
    structAcqInfoEx&,
    const CStream_0x0001*,
    const CSubStreamAscan_0x0103* hdr,
    const void* bufferMax,
    const void*,
    const void*)
{
    auto* self = static_cast<AcquisitionSource*>(p);
    if (!self || !hdr || !bufferMax) {
        return 0;
    }

    self->handle(hdr, bufferMax);
    return 0;
}

void AcquisitionSource::handle(
    const CSubStreamAscan_0x0103* hdr,
    const void* buffer)
{
    FrameHandler localHandler;
    bool running = false;

    {
        std::lock_guard lock(mutex_);
        localHandler = handler_;
        running = control_.isRunning();
    }

    if (!running || !localHandler) {
        return;
    }

    const auto byteCount =
        static_cast<std::size_t>(hdr->dataSize) *
        static_cast<std::size_t>(hdr->dataCount);

    RawAScanFrame frame;
    frame.dataSize = static_cast<int>(hdr->dataSize);
    frame.dataCount = static_cast<int>(hdr->dataCount);
    frame.cycle = static_cast<int>(hdr->cycle);
    frame.bitSize = static_cast<int>(hdr->bitSize);
    frame.sign = hdr->sign != 0;
    frame.data.resize(byteCount);

    if (byteCount != 0) {
        std::memcpy(frame.data.data(), buffer, byteCount);
    }

    localHandler(std::move(frame));
}

} // namespace scanlab::acquisition::ascan