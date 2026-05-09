#pragma once

#include "scanlab/health/health_error.h"
#include <expected>
#include <memory>

class DeviceContext;

namespace scanlab::health
{
class TemperatureReader;
}

class TemperatureService
{
public:
    explicit TemperatureService(DeviceContext& context);

    std::expected<int, scanlab::health::HealthError> readMax() const;

    ~TemperatureService();

private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::health::TemperatureReader> temperatureReader_;
};
