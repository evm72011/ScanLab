#include "scanlab/hardware/health_monitor.h"

#include <UTDriverOEMPA.h>

#include <algorithm>

namespace scanlab::hardware {

bool HealthMonitor::TemperatureSnapshot::empty() const
{
    return sensors.empty() && maxPerBoardCelsius.empty();
}

std::optional<int> HealthMonitor::TemperatureSnapshot::overallMaxCelsius() const
{
    if (maxPerBoardCelsius.empty()) {
        return std::nullopt;
    }

    return *std::max_element(maxPerBoardCelsius.begin(), maxPerBoardCelsius.end());
}

void HealthMonitor::setDevice(Device* device)
{
    device_ = device;
}

Device* HealthMonitor::device()
{
    return device_;
}

const Device* HealthMonitor::device() const
{
    return device_;
}

std::optional<HealthMonitor::TemperatureSnapshot>
HealthMonitor::readTemperatureSnapshot() const
{
    if (device_ == nullptr) {
        return std::nullopt;
    }

    auto* native = device_->get();
    if (native == nullptr) {
        return std::nullopt;
    }

    auto* sw = native->GetSWDeviceOEMPA();
    if (sw == nullptr) {
        return std::nullopt;
    }

    int boardCount = 0;
    int sensorCountMax = 0;
    if (!sw->GetTemperatureCount(boardCount, sensorCountMax)) {
        return std::nullopt;
    }

    if (boardCount <= 0) {
        return TemperatureSnapshot{};
    }

    if (!native->LockDevice(eAcqContinue)) {
        return std::nullopt;
    }

    TemperatureSnapshot snapshot;
    bool ok = true;

    for (int board = 0; board < boardCount; ++board) {
        int sensorCount = 0;
        if (!sw->GetTemperatureSensorCount(board, sensorCount)) {
            ok = false;
            break;
        }

        for (int sensor = 0; sensor < sensorCount; ++sensor) {
            short value = 0;
            if (!native->GetTemperatureSensor(board, sensor, &value)) {
                ok = false;
                break;
            }

            snapshot.sensors.push_back(TemperatureSensor{
                .board = board,
                .sensor = sensor,
                .valueCelsius = static_cast<int>(value)
            });
        }

        if (!ok) {
            break;
        }

        short maxValue = 0;
        if (!native->GetTemperatureMaxHW(board, &maxValue)) {
            ok = false;
            break;
        }

        snapshot.maxPerBoardCelsius.push_back(static_cast<int>(maxValue));
    }

    const bool unlockOk = native->UnlockDevice();

    if (!ok || !unlockOk) {
        return std::nullopt;
    }

    return snapshot;
}

} // namespace scanlab::hardware