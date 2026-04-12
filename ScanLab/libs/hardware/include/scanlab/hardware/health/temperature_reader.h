#pragma once

//#include <cstddef>
#include <optional>
#include <expected>
//#include <vector>

#include "scanlab/hardware/device/device.h"
#include "scanlab/hardware/health/health_types.h"
#include "scanlab/hardware/health/health_topology.h"

namespace scanlab::hardware {

class TemperatureReader
{
public:
    explicit TemperatureReader(Device& device);
    [[nodiscard]] std::expected<int, HealthErrorCodes> readMax() const;

private:
    /*
    struct Topology
    {
        CHWDeviceOEMPA* hw = nullptr;
        int boardCount = 0;
        std::vector<int> sensorCountPerBoard;
        std::size_t totalSensorCount = 0;

        [[nodiscard]] bool empty() const;
    };
*/

private:
    [[nodiscard]] std::expected<void, HealthErrorCodes> ensureTopology() const;
    void invalidateTopology() const;

private:
    Device& device_;
    mutable std::optional<HealthTopology> topology_;
};

} // namespace scanlab::hardware