#include "scanlab/hardware/acquisition/acquisition_stream.h"

#include <UTDriverOEMPA.h>

namespace scanlab::hardware {

AcquisitionStream::AcquisitionStream(Device& device)
    : device_(device)
{
}

AcquisitionStream::~AcquisitionStream()
{
    stop();
}

CHWDeviceOEMPA* AcquisitionStream::native()
{
    return device_.get();
}

const CHWDeviceOEMPA* AcquisitionStream::native() const
{
    return device_.get();
}

void AcquisitionStream::registerCallbacks()
{
    auto* hw = native();
    if (!hw) {
        return;
    }

    hw->SetAcquisitionParameter(this);
    hw->SetAcquisitionAscan_0x00010103(&AcquisitionStream::callback);
}

void AcquisitionStream::unregisterCallbacks()
{
    auto* hw = native();
    if (!hw) {
        return;
    }

    hw->SetAcquisitionAscan_0x00010103(nullptr);
    hw->SetAcquisitionParameter(nullptr);
}

UINT WINAPI AcquisitionStream::callback(
    void* p,
    structAcqInfoEx&,
    const CStream_0x0001*,
    const CSubStreamAscan_0x0103* hdr,
    const void* buffer,
    const void*,
    const void*)
{
    auto* self = static_cast<AcquisitionStream*>(p);
    if (!self || !hdr || !buffer) {
        return 0;
    }

    self->handle(hdr, buffer);
    return 0;
}

void AcquisitionStream::handle(const CSubStreamAscan_0x0103* hdr, const void* buffer)
{
    FrameHandler localHandler;
    bool localRunning = false;

    {
        std::lock_guard lock(mutex_);
        localHandler = handler_;
        localRunning = running_;
    }

    if (!localRunning || !localHandler) {
        return;
    }

    RawAcquisitionFrame frame;
    frame.dataSize = static_cast<int>(hdr->dataSize);
    frame.dataCount = static_cast<int>(hdr->dataCount);
    frame.cycle = static_cast<int>(hdr->cycle);
    frame.bitSize = static_cast<int>(hdr->bitSize);
    frame.sign = hdr->sign != 0;
    frame.buffer = buffer;

    localHandler(std::move(frame));
}

void AcquisitionStream::setFrameHandler(FrameHandler handler)
{
    std::lock_guard lock(mutex_);
    handler_ = std::move(handler);
}

bool AcquisitionStream::start()
{
    auto* hw = native();
    if (!hw) {
        return false;
    }

    registerCallbacks();

    if (!hw->LockDevice()) {
        unregisterCallbacks();
        return false;
    }

    if (!hw->UnlockDevice(eAcqOn)) {
        unregisterCallbacks();
        return false;
    }

    {
        std::lock_guard lock(mutex_);
        running_ = true;
    }

    return true;
}

void AcquisitionStream::stop()
{
    auto* hw = native();

    {
        std::lock_guard lock(mutex_);
        running_ = false;
    }

    if (hw && hw->LockDevice()) {
        hw->UnlockDevice(eAcqOff);
    }

    unregisterCallbacks();
}

bool AcquisitionStream::isRunning() const
{
    std::lock_guard lock(mutex_);
    return running_;
}

} // namespace scanlab::hardware