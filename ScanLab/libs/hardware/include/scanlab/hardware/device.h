#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <UTDriverOEMPA.h>

#include "scanlab/hardware/device_type.h"

namespace scanlab::hardware {

class Device
{
public:

public:
    Device();
    ~Device();

    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;

    Device(Device&&) noexcept;
    Device& operator=(Device&&) noexcept;

    bool setDevice(DeviceType type);
    bool connect(const std::wstring& address);
    void disconnect();

    bool hasDevice() const;
    bool isConnected() const;

    CHWDeviceOEMPA* get();
    const CHWDeviceOEMPA* get() const;

private:
    std::unique_ptr<CHWDeviceOEMPA> device_;
    bool connected_ = false;
};
}
