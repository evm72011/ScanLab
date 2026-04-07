#include "runtime/device/device_context.h"

#include "scanlab/hardware/device.h"

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

//void DeviceContext::setDevice(std::unique_ptr<scanlab::hardware::Device> device)
//{
//    device_ = std::move(device);
//}

bool DeviceContext::hasDevice() const
{
    return device_ != nullptr;
}

void DeviceContext::reset()
{
    device_.reset();
}
