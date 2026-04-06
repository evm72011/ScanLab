#pragma once

#include <memory>

namespace scanlab::hardware {
class Device;
}

class DeviceContext
{
public:
    DeviceContext();

    DeviceContext(const DeviceContext&) = delete;
    DeviceContext& operator=(const DeviceContext&) = delete;

    ~DeviceContext();

    scanlab::hardware::Device* device();
    const scanlab::hardware::Device* device() const;

    void setDevice(std::unique_ptr<scanlab::hardware::Device> device);

    bool hasDevice() const;
    void reset();

private:
    std::unique_ptr<scanlab::hardware::Device> device_;
};
