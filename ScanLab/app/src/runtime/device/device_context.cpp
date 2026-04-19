#include "runtime/device/device_context.h"

#include "scanlab/device/device.h"

DeviceContext::DeviceContext()
    : device_(std::make_unique<scanlab::hardware::Device>())
{
}

DeviceContext::~DeviceContext() = default;

scanlab::hardware::Device* DeviceContext::device()
{
    return device_.get();
}

const scanlab::hardware::Device* DeviceContext::device() const
{
    return device_.get();
}
