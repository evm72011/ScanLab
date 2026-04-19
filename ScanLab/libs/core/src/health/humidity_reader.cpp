#include "scanlab/hardware/health/humidity_reader.h"
#include "scanlab/hardware/health/humidity_topology_api.h"

namespace scanlab::hardware {

HumidityReader::HumidityReader(Device& device)
    : device_(device)
{
}

std::expected<int, HealthError> HumidityReader::readMax() const {
    const auto topologyResult = topology_.ensure(device_, HumidityTopologyApi{});

    if (!topologyResult) {
        return std::unexpected(topologyResult.error());
    }

    auto* hw = device_.get();
    if (hw == nullptr) {
        topology_.reset();
        return std::unexpected(HardwareError::HardwareNotSet);
    }

    if (hw->GetSWDeviceOEMPA() == nullptr) {
        topology_.reset();
        return std::unexpected(HardwareError::OempaInterfaceUnavailable);
    }

    if (!hw->LockDevice(eAcqContinue)) {
        return std::unexpected(HardwareError::DeviceLockFailed);
    }

    bool ok = true;
    size_t sensorIdx = 0;
    std::vector<WORD> values(static_cast<std::size_t>(topology_.totalSensorCount()), 0);
    for (int board = 0; board < topology_.boardCount() && ok; ++board) {
        const int sensorCount = topology_.sensorCountPerBoard()[board];
        for (int sensor = 0; sensor < sensorCount; ++sensor) {
            if (!hw->GetHumiditySensor(board, sensor, &values[sensorIdx])) {
                ok = false;
                break;
            }
            sensorIdx++;
        }
    }

    const bool unlockOk = hw->UnlockDevice(eAcqContinue);
    if (!ok || !unlockOk || values.empty()) {
        return std::unexpected(HealthErrorKind::SensorDataUnavailable);
    }

    short result = values[0];
    for (short value : values) {
        result = std::max(result, value);
    }

    return static_cast<int>(result);
}
}// namespace scanlab::hardware
