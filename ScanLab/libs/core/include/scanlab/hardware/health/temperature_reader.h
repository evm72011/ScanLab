#pragma once

#include <expected>

#include "scanlab/hardware/device/device.h"
#include "scanlab/hardware/health/health_error.h"
#include "scanlab/hardware/health/health_topology.h"

namespace scanlab::hardware {

class TemperatureReader
{
public:
    explicit TemperatureReader(Device& device);
    [[nodiscard]] std::expected<int, HealthError> readMax() const;

private:
    Device& device_;
    mutable HealthTopology topology_;
};

} // namespace scanlab::hardware