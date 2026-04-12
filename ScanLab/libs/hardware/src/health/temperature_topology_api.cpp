#include "scanlab/hardware/health/temperature_topology_api.h"

#include <Windows.h>
#include <UTDriverOEMPA.h>

namespace scanlab::hardware {

bool TemperatureTopologyApi::getBoardCount(CSWDeviceOEMPA* sw, int& boardCount, int& sensorCountMax) const
{
    return sw->GetTemperatureCount(boardCount, sensorCountMax);
}

bool TemperatureTopologyApi::getSensorCount(CSWDeviceOEMPA* sw, int board, int& sensorCount) const
{
    return sw->GetTemperatureSensorCount(board, sensorCount);
}

} // namespace scanlab::hardware