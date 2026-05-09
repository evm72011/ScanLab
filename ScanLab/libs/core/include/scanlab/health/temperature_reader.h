#pragma once

#include <expected>

#include "scanlab/device/device.h"
#include "scanlab/health/health_error.h"
#include "scanlab/health/health_topology.h"

namespace scanlab::health
{

class TemperatureReader
{
public:
    explicit TemperatureReader(scanlab::device::Device& device);
    [[nodiscard]] std::expected<int, HealthError> readMax() const;

private:
    scanlab::device::Device& device_;
    mutable HealthTopology topology_;
};

} // namespace scanlab::health