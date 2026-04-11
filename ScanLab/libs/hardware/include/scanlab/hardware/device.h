#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <expected>
#include <UTDriverOEMPA.h>

#include "scanlab/hardware/device_type.h"
#include "scanlab/hardware/connection_error_codes.h"

namespace scanlab::hardware {

class Device
{
public:
    struct Topology
    {
        int boardCount = 0;
        std::vector<int> sensorCountPerBoard;
        std::size_t totalSensorCount = 0;

        [[nodiscard]] bool empty() const;
    };
public:
    Device();
    ~Device();

    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;

    Device(Device&&) noexcept;
    Device& operator=(Device&&) noexcept;

    bool ensureDevice(DeviceType type);

    std::expected<void,ConnectionErrorCodes> connect(const std::wstring& address);
    bool disconnect();

    bool hasDevice() const;
    bool isConnected() const;

    CHWDeviceOEMPA* get();
    const CHWDeviceOEMPA* get() const;
private:
    //[[nodiscard]] std::expected<void, TemperatureErrorCodes> ensureTopology() const;
    //void invalidateTopology() const;
private:
    std::unique_ptr<CHWDeviceOEMPA> device_;
    std::optional<DeviceType> type_;
    std::optional<Topology> topology_;
};

} // namespace scanlab::hardware
