#pragma once

#include <memory>
#include <expected>
#include "scanlab/hardware/temperature_types.h"

class DeviceContext;

namespace scanlab::hardware {
class TemperatureReader;
}

class HealthService
{
public:
    explicit HealthService(DeviceContext& context);

    std::expected<int, scanlab::hardware::TemperatureErrorCodes> readMax() const;

    ~HealthService();
private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::hardware::TemperatureReader> temperatureReader_;
};
