#pragma once

#include <cstddef>
#include <optional>
#include <vector>

#include "scanlab/hardware/device.h"
#include "scanlab/hardware/temperature_types.h"

namespace scanlab::hardware {

class TemperatureReader
{
public:
    explicit TemperatureReader(Device& device);

    [[nodiscard]] std::optional<TemperatureSnapshot> read() const;

private:
    struct Topology
    {
        CHWDeviceOEMPA* hw = nullptr;
        int boardCount = 0;
        std::vector<int> sensorCountPerBoard;
        std::size_t totalSensorCount = 0;

        [[nodiscard]] bool empty() const;
    };

private:
    [[nodiscard]] bool ensureTopology() const;
    void invalidateTopology() const;

private:
    Device& device_;
    mutable std::optional<Topology> topology_;
};

} // namespace scanlab::hardware