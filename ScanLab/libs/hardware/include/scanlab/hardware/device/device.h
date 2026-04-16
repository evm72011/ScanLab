#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <optional>
#include <expected>
#include <UTDriverOEMPA.h>

#include "scanlab/hardware/device/device_type.h"
#include "scanlab/hardware/device/connection_error_codes.h"
#include "scanlab/hardware/device/connection_result.h"

namespace scanlab::hardware {

class Device
{

public:
    Device();
    ~Device();

    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;

    Device(Device&&) noexcept;
    Device& operator=(Device&&) noexcept;

    bool ensureDevice(DeviceType type);

    std::expected<ConnectionResult,ConnectionErrorCodes> connect(const std::wstring& address);
    bool disconnect();

    bool hasDevice() const;
    bool isConnected() const;

    CHWDeviceOEMPA* get();
    const CHWDeviceOEMPA* get() const;
private:
    std::unique_ptr<CHWDeviceOEMPA> device_;
    std::optional<DeviceType> type_;
#ifdef MOCK_DEVICE
    bool connected_ = false;
#endif
};

} // namespace scanlab::hardware
