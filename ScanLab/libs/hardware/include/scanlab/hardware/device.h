#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <UTDriverOEMPA.h>

#include "scanlab/hardware/device_type.h"
#include "scanlab/hardware/connect_result.h"

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

    void resetDevice();
    bool setDevice(DeviceType type);

    ConnectResult connect(const std::wstring& address);
    bool disconnect();

    bool hasDevice() const;
    bool isConnected() const;

    CHWDeviceOEMPA* get();
    const CHWDeviceOEMPA* get() const;

private:
    std::unique_ptr<CHWDeviceOEMPA> device_;
};

} // namespace scanlab::hardware
