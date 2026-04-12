#pragma once

#include <vector>

class CHWDeviceOEMPA;

namespace scanlab::hardware {
struct HealthTopology
{
    CHWDeviceOEMPA* hw = nullptr;
    int boardCount = 0;
    std::vector<int> sensorCountPerBoard;
    std::size_t totalSensorCount = 0;

    [[nodiscard]] bool empty() const { return boardCount > 0; }
};
}// namespace scanlab::hardware