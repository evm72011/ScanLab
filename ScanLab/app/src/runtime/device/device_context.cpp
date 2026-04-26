#include "runtime/device/device_context.h"

#include "scanlab/device/device.h"

namespace sd = scanlab::device;

DeviceContext::DeviceContext()
    : device_(std::make_unique<sd::Device>())
{
}

DeviceContext::~DeviceContext() = default;

sd::Device* DeviceContext::device()
{
    return device_.get();
}

const sd::Device* DeviceContext::device() const
{
    return device_.get();
}

scanlab::acquisition::AcquisitionSetupSnapshot& DeviceContext::setupSnapshot()
{
    return setupSnapshot_;
}
