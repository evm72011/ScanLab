#pragma once

#include <memory>
#include <expected>
#include "scanlab/hardware/health/health_error.h"

class DeviceContext;

namespace scanlab::hardware {
class HumidityReader;
}

class HumidityService
{
public:
    explicit HumidityService(DeviceContext& context);

    std::expected<int, scanlab::hardware::HealthError> readMax() const;

    ~HumidityService();
private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::hardware::HumidityReader> humidityReader_;
};
