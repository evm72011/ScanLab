#include "scanlab/acquisition/acquisition_control.h"

#include <UTDriverOEMPA.h>

namespace sd = scanlab::device;

namespace scanlab::acquisition {

AcquisitionControl::AcquisitionControl(sd::Device& device)
    : device_(device)
{
}

std::expected<void, AcquisitionError> AcquisitionControl::start(
    const std::function<void()>& registerCallbacks,
    const std::function<void()>& unregisterCallbacks)
{
    auto* hw = device_.get();
    if (!hw) {
        return std::unexpected(sd::HardwareError::HardwareNotSet);
    }

    {
        std::lock_guard lock(mutex_);
        if (running_) {
            return {};
        }
        running_ = true;
    }

    registerCallbacks();

    if (!hw->LockDevice()) {
        unregisterCallbacks();

        std::lock_guard lock(mutex_);
        running_ = false;

        return std::unexpected(sd::HardwareError::DeviceLockFailed);
    }

    if (!hw->UnlockDevice(eAcqOn)) {
        unregisterCallbacks();

        std::lock_guard lock(mutex_);
        running_ = false;

        return std::unexpected(sd::HardwareError::DeviceUnlockFailed);
    }

    return {};
}

void AcquisitionControl::stop(const std::function<void()>& unregisterCallbacks)
{
    bool wasRunning = false;

    {
        std::lock_guard lock(mutex_);
        wasRunning = running_;
        running_ = false;
    }

    auto* hw = device_.get();

    if (wasRunning && hw && hw->LockDevice()) {
        hw->UnlockDevice(eAcqOff);
    }

    unregisterCallbacks();
}

bool AcquisitionControl::isRunning() const
{
    std::lock_guard lock(mutex_);
    return running_;
}

} // namespace scanlab::acquisition