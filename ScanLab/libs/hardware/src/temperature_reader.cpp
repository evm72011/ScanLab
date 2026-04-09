#include "scanlab/hardware/temperature_reader.h"

#include <UTDriverOEMPA.h>

#include <algorithm>
#include <utility>
#include <iostream>

namespace scanlab::hardware {

TemperatureReader::TemperatureReader(Device& device)
    : device_(device)
{
}

bool TemperatureSnapshot::empty() const
{
    return sensors.empty() && boardMaxCelsius.empty();
}

std::optional<int> TemperatureSnapshot::overallMaxCelsius() const
{
    if (boardMaxCelsius.empty()) {
        return std::nullopt;
    }

    return *std::max_element(boardMaxCelsius.begin(), boardMaxCelsius.end());
}

bool TemperatureReader::Topology::empty() const
{
    return boardCount <= 0;
}

void TemperatureReader::invalidateTopology() const
{
    topology_.reset();
}

bool TemperatureReader::ensureTopology() const
{
    std::cout << "TemperatureReader::ensureTopology::start\n";
    auto* hw = device_.get();
    if (hw == nullptr) {
        invalidateTopology();
        return false;
    }

    if (topology_.has_value() && topology_->hw == hw) {
        return true;
    }

    auto* sw = hw->GetSWDeviceOEMPA();
    if (sw == nullptr) {
        invalidateTopology();
        return false;
    }

    int boardCount = 0;
    int sensorCountMax = 0;
    if (!sw->GetTemperatureCount(boardCount, sensorCountMax)) {
        invalidateTopology();
        return false;
    }

    if (boardCount < 0) {
        invalidateTopology();
        return false;
    }

    Topology topology;
    topology.hw = hw;
    topology.boardCount = boardCount;
    topology.sensorCountPerBoard.reserve(static_cast<std::size_t>(boardCount));

    std::size_t totalSensorCount = 0;

    for (int board = 0; board < boardCount; ++board) {
        int sensorCount = 0;
        if (!sw->GetTemperatureSensorCount(board, sensorCount)) {
            invalidateTopology();
            return false;
        }

        if (sensorCount < 0) {
            invalidateTopology();
            return false;
        }

        topology.sensorCountPerBoard.push_back(sensorCount);
        totalSensorCount += static_cast<std::size_t>(sensorCount);
    }

    topology.totalSensorCount = totalSensorCount;
    topology_ = std::move(topology);
    std::cout << "TemperatureReader::ensureTopology::success\n";

    return true;
}

std::optional<TemperatureSnapshot> TemperatureReader::read() const
{
    if (!ensureTopology()) {
        return std::nullopt;
    }

    auto* hw = device_.get();
    if (hw == nullptr) {
        invalidateTopology();
        return std::nullopt;
    }

    const Topology& topology = *topology_;

    if (topology.hw != hw) {
        invalidateTopology();
        if (!ensureTopology()) {
            return std::nullopt;
        }
    }

    const Topology& currentTopology = *topology_;

    if (currentTopology.empty()) {
        return TemperatureSnapshot{};
    }

    if (!hw->LockDevice(eAcqContinue)) {
        return std::nullopt;
    }

    TemperatureSnapshot snapshot;
    snapshot.sensors.reserve(currentTopology.totalSensorCount);
    snapshot.boardMaxCelsius.reserve(
        static_cast<std::size_t>(currentTopology.boardCount));

    bool ok = true;

    for (int board = 0; board < currentTopology.boardCount && ok; ++board) {
        const int sensorCount = currentTopology.sensorCountPerBoard[board];

        for (int sensor = 0; sensor < sensorCount; ++sensor) {
            short value = 0;
            if (!hw->GetTemperatureSensor(board, sensor, &value)) {
                ok = false;
                break;
            }

            snapshot.sensors.push_back(TemperatureSensorReading{
                .board = board,
                .sensor = sensor,
                .valueCelsius = static_cast<int>(value)
            });
        }

        if (!ok) {
            break;
        }

        short maxValue = 0;
        if (!hw->GetTemperatureMaxHW(board, &maxValue)) {
            ok = false;
            break;
        }

        snapshot.boardMaxCelsius.push_back(static_cast<int>(maxValue));
    }

    const bool unlockOk = hw->UnlockDevice(eAcqContinue);
    if (!ok || !unlockOk) {
        return std::nullopt;
    }

    return snapshot;
}

} // namespace scanlab::hardware