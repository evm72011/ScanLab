#pragma once

#include "scanlab/health/health_error.h"
#include <expected>
#include <memory>

class DeviceContext;

namespace scanlab::health
{
class HumidityReader;
}

class HumidityService
{
public:
    explicit HumidityService(DeviceContext& context);

    std::expected<int, scanlab::health::HealthError> readMax() const;

    ~HumidityService();

private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::health::HumidityReader> humidityReader_;
};
