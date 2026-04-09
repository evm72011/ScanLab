#pragma once

#include <memory>
#include <optional>
#include "scanlab/hardware/temperature_types.h"

class DeviceContext;

namespace scanlab::hardware {
class TemperatureReader;
}

class HealthService
{
public:
    explicit HealthService(DeviceContext& context);

    std::optional<scanlab::hardware::TemperatureSnapshot> readTemperature() const;

    ~HealthService();
private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::hardware::TemperatureReader> temperatureReader_;
};
