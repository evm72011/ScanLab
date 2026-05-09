#include "runtime/device/device_context.h"

#include "scanlab/device/device.h"

namespace sd = scanlab::device;

DeviceContext::DeviceContext(std::filesystem::path licensePath, std::string licensePublicKeyBase64)
    : device_(
          std::make_unique<sd::Device>(std::move(licensePath), std::move(licensePublicKeyBase64)))
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
