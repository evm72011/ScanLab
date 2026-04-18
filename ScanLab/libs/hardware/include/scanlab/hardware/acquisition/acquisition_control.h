#pragma once

#include "scanlab/hardware/acquisition/acquisition_error.h"
#include "scanlab/hardware/device/device.h"

#include <expected>
#include <functional>
#include <mutex>

namespace scanlab::hardware {

class AcquisitionControl
{
public:
    explicit AcquisitionControl(Device& device);

    std::expected<void, AcquisitionError> start(
        const std::function<void()>& registerCallbacks,
        const std::function<void()>& unregisterCallbacks);

    void stop(const std::function<void()>& unregisterCallbacks);

    bool isRunning() const;

private:
    Device& device_;
    bool running_ = false;
    mutable std::mutex mutex_;
};

} // namespace scanlab::hardware