#pragma once

#include <memory>
#include <expected>
#include "scanlab/hardware/health/health_error.h"

class DeviceContext;

namespace scanlab::hardware {
class TemperatureReader;
}

class TemperatureService
{
public:
    explicit TemperatureService(DeviceContext& context);

    std::expected<int, scanlab::hardware::HealthErrorCodes> readMax() const;

    ~TemperatureService();
private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::hardware::TemperatureReader> temperatureReader_;
};
