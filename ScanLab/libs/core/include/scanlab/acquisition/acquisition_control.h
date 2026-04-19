#pragma once

#include "scanlab/acquisition/acquisition_error.h"
#include "scanlab/device/device.h"

#include <expected>
#include <functional>
#include <mutex>

namespace scanlab::acquisition {

class AcquisitionControl
{
public:
    explicit AcquisitionControl(scanlab::device::Device& device);

    std::expected<void, AcquisitionError> start(
        const std::function<void()>& registerCallbacks,
        const std::function<void()>& unregisterCallbacks);

    void stop(const std::function<void()>& unregisterCallbacks);

    bool isRunning() const;

private:
    scanlab::device::Device& device_;
    bool running_ = false;
    mutable std::mutex mutex_;
};

} // namespace scanlab::acquisition