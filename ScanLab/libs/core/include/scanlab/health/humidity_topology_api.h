#pragma once

class CSWDeviceOEMPA;

namespace scanlab::health
{

struct HumidityTopologyApi
{
    bool getBoardCount(CSWDeviceOEMPA* sw, int& boardCount, int& sensorCountMax) const;
    bool getSensorCount(CSWDeviceOEMPA* sw, int board, int& sensorCount) const;
};

} // namespace scanlab::health