#include "scanlab/health/humidity_topology_api.h"

#include <Windows.h>
#include <UTDriverOEMPA.h>

namespace scanlab::health {

bool HumidityTopologyApi::getBoardCount(CSWDeviceOEMPA* sw, int& boardCount, int& sensorCountMax) const
{
    return sw->GetHumidityCount(boardCount, sensorCountMax);
}

bool HumidityTopologyApi::getSensorCount(CSWDeviceOEMPA* sw, int board, int& sensorCount) const
{
    return sw->GetHumiditySensorCount(board, sensorCount);
}

} // namespace scanlab::health