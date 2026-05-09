#pragma once

#include <filesystem>
#include <memory>
#include <string>

namespace scanlab::device
{
class Device;
}

class DeviceContext
{
public:
    DeviceContext(std::filesystem::path licensePath, std::string licensePublicKeyBase64);

    DeviceContext(const DeviceContext&) = delete;
    DeviceContext& operator=(const DeviceContext&) = delete;

    ~DeviceContext();

    scanlab::device::Device* device();
    const scanlab::device::Device* device() const;

private:
    std::unique_ptr<scanlab::device::Device> device_;
};
