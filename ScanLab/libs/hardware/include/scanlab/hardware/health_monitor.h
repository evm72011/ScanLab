#pragma once

#include "scanlab/hardware/device.h"

#include <optional>
#include <vector>

namespace scanlab::hardware {

class [[deprecated("Use TemperatureReader")]] HealthMonitor
{
public:
    struct TemperatureSensor
    {
        int board = 0;
        int sensor = 0;
        int valueCelsius = 0;
    };

    struct TemperatureSnapshot
    {
        std::vector<TemperatureSensor> sensors;
        std::vector<int> maxPerBoardCelsius;

        bool empty() const;
        std::optional<int> overallMaxCelsius() const;
    };

public:
    HealthMonitor() = default;

    void setDevice(Device* device);
    Device* device();
    const Device* device() const;

    std::optional<TemperatureSnapshot> readTemperatureSnapshot() const;

private:
    Device* device_ = nullptr;
};

} // namespace scanlab::hardware