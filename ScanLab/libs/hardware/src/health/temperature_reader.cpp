#include "scanlab/hardware/health/temperature_reader.h"

#include <UTDriverOEMPA.h>

#include <algorithm>
#include <utility>

namespace scanlab::hardware {

TemperatureReader::TemperatureReader(Device& device)
    : device_(device)
{
}

void TemperatureReader::invalidateTopology() const
{
    topology_.reset();
}

std::expected<void, HealthErrorCodes> TemperatureReader::ensureTopology() const
{
    auto* hw = device_.get();
    if (hw == nullptr) {
        invalidateTopology();
        return std::unexpected(HealthErrorCodes::HardwareNotSet);
    }

    if (topology_.has_value() && topology_->hw == hw) {
        return {};
    }

    auto* sw = hw->GetSWDeviceOEMPA();
    if (sw == nullptr) {
        invalidateTopology();
        return std::unexpected(HealthErrorCodes::OempaInterfaceUnavailable);;
    }

    int boardCount = 0;
    int sensorCountMax = 0;
    if (!sw->GetTemperatureCount(boardCount, sensorCountMax)) {
        invalidateTopology();
        return std::unexpected(HealthErrorCodes::BoardToppologyUnavailable);
    }

    if (boardCount < 0) {
        invalidateTopology();
        return std::unexpected(HealthErrorCodes::BoardTopologyErrors);
    }

    HealthTopology topology;
    topology.hw = hw;
    topology.boardCount = boardCount;
    topology.sensorCountPerBoard.reserve(static_cast<std::size_t>(boardCount));

    std::size_t totalSensorCount = 0;

    for (int board = 0; board < boardCount; ++board) {
        int sensorCount = 0;
        if (!sw->GetTemperatureSensorCount(board, sensorCount)) {
            invalidateTopology();
            return std::unexpected(HealthErrorCodes::SensorTopologyUnavailable);
        }

        if (sensorCount < 0) {
            invalidateTopology();
            return std::unexpected(HealthErrorCodes::SensorTopologyErrors);
        }

        topology.sensorCountPerBoard.push_back(sensorCount);
        totalSensorCount += static_cast<std::size_t>(sensorCount);
    }

    topology.totalSensorCount = totalSensorCount;
    topology_ = std::move(topology);
    return {};
}

std::expected<int, HealthErrorCodes> TemperatureReader::readMax() const {
    const auto topologyResult = ensureTopology();
    if (!topologyResult) {
        return std::unexpected(topologyResult.error());
    }

    auto* hw = device_.get();
    if (hw == nullptr) {
        invalidateTopology();
        return std::unexpected(HealthErrorCodes::HardwareNotSet);
    }

    auto* sw = hw->GetSWDeviceOEMPA();
    if (sw == nullptr) {
        return std::unexpected(HealthErrorCodes::OempaInterfaceUnavailable);
    }

    if (!hw->LockDevice(eAcqContinue)) {
        return std::unexpected(HealthErrorCodes::DeviceLockFailed);
    }

    bool ok = true;
    size_t sensorIdx = 0;
    std::vector<short> values(static_cast<std::size_t>(topology_->totalSensorCount), 0);
    for (int board = 0; board < topology_->boardCount && ok; ++board) {
        const int sensorCount = topology_->sensorCountPerBoard[board];
        for (int sensor = 0; sensor < sensorCount; ++sensor) {
            if (!hw->GetTemperatureSensor(board, sensor, &values[sensorIdx])) {
                ok = false;
                break;
            }
            sensorIdx++;
        }
    }

    const bool unlockOk = hw->UnlockDevice(eAcqContinue);
    if (!ok || !unlockOk || values.empty()) {
        return std::unexpected(HealthErrorCodes::SensorDataUnavailable);
    }

    short result = values[0];
    for (short value : values) {
        result = std::max(result, value);
    }

    return static_cast<int>(result);
}

/*
std::expected<int, TemperatureErrorCodes> TemperatureReader::readMax() const {
    const auto topologyResult = ensureTopology();
    if (!topologyResult) {
        return std::unexpected(topologyResult.error());
    }

    auto* hw = device_.get();
    if (hw == nullptr) {
        invalidateTopology();
        return std::unexpected(TemperatureErrorCodes::HardwareNotSet);
    }

    auto* sw = hw->GetSWDeviceOEMPA();
    if (sw == nullptr) {
        return std::unexpected(TemperatureErrorCodes::OempaInterfaceUnavailable);
    }

    if (!hw->LockDevice(eAcqContinue)) {
        return std::unexpected(TemperatureErrorCodes::DeviceLockFailed);
    }

    bool ok = true;
    std::vector<short> values(static_cast<std::size_t>(topology_->boardCount), 0);
    for (int board = 0; board < topology_->boardCount && ok; ++board) {
        if (!hw->GetTemperatureMaxHW(board, &values[static_cast<std::size_t>(board)])) {    // always 42
            ok = false;
            break;
        }
    }

    const bool unlockOk = hw->UnlockDevice(eAcqContinue);
    if (!ok || !unlockOk || values.empty()) {
        return std::unexpected(TemperatureErrorCodes::MaxBoardTemperatureUnavailable);
    }

    short result = values[0];
    for (short value : values) {
        result = std::max(result, value);
    }

    return static_cast<int>(result);
}
*/

} // namespace scanlab::hardware