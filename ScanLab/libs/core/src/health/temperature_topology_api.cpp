#include "scanlab/health/temperature_topology_api.h"


#include "scanlab/oempa/sdk.h" // IWYU pragma: keep

namespace scanlab::health
{

bool TemperatureTopologyApi::getBoardCount(CSWDeviceOEMPA* sw,
    int& boardCount,
    int& sensorCountMax) const
{
    return sw->GetTemperatureCount(boardCount, sensorCountMax);
}

bool TemperatureTopologyApi::getSensorCount(CSWDeviceOEMPA* sw, int board, int& sensorCount) const
{
    return sw->GetTemperatureSensorCount(board, sensorCount);
}

} // namespace scanlab::health