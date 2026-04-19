#pragma once

#include "scanlab/device/device.h"
#include "scanlab/health/health_error.h"
#include "scanlab/health/health_topology.h"

namespace scanlab::hardware {

class HumidityReader
{
public:
    explicit HumidityReader(Device& device);
    [[nodiscard]] std::expected<int, HealthError> readMax() const;

private:
    Device& device_;
    mutable HealthTopology topology_;
};
}// namespace scanlab::hardware
