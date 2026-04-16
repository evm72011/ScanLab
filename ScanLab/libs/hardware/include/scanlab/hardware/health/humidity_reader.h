#pragma once

#include "scanlab/hardware/device/device.h"
#include "scanlab/hardware/health/health_error.h"
#include "scanlab/hardware/health/health_topology.h"

namespace scanlab::hardware {

class HumidityReader
{
public:
    explicit HumidityReader(Device& device);
    [[nodiscard]] std::expected<int, HealthErrorCodes> readMax() const;

private:
    Device& device_;
    mutable HealthTopology topology_;
};
}// namespace scanlab::hardware
