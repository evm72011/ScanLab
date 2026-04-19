#pragma once

#include <memory>

namespace scanlab::device {
class Device;
}

class DeviceContext
{
public:
    DeviceContext();

    DeviceContext(const DeviceContext&) = delete;
    DeviceContext& operator=(const DeviceContext&) = delete;

    ~DeviceContext();

    scanlab::device::Device* device();
    const scanlab::device::Device* device() const;

private:
    std::unique_ptr<scanlab::device::Device> device_;
};
