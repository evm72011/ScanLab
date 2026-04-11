#pragma once

#include <memory>
#include <expected>
#include "scanlab/hardware/health/temperature_types.h"

class DeviceContext;

namespace scanlab::hardware {
class TemperatureReader;
}

class TemperatureService
{
public:
    explicit TemperatureService(DeviceContext& context);

    std::expected<int, scanlab::hardware::TemperatureErrorCodes> readMax() const;

    ~TemperatureService();
private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::hardware::TemperatureReader> temperatureReader_;
};
