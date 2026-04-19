#pragma once

#include <memory>
#include <expected>
#include "scanlab/health/health_error.h"

class DeviceContext;

namespace scanlab::health {
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
