#include "scanlab/hardware/health_monitor.h"

#include <UTDriverOEMPA.h>
#include <UTDriverOEMMC.h>

#include <algorithm>
#include <iostream>

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

    auto* hw = dynamic_cast<CHWDeviceOEMMC2*>(native); // TODO other types
    if (hw == nullptr) {
        std::cout << "[TEMP] cast to CHWDeviceOEMMC failed" << std::endl;
        return std::nullopt;
    }

    auto* sw = hw->GetSWDeviceOEMPA();
    if (sw == nullptr) {
        return std::nullopt;
    }

    int boardCount = 0;
    int sensorCountMax = 0;
    if (!sw->GetTemperatureCount(boardCount, sensorCountMax)) {
        return std::nullopt;
    }

    std::cout << "[TEMP] boardCount=" << boardCount
              << " sensorCountMax=" << sensorCountMax
              << std::endl;

    if (boardCount <= 0) {
        return TemperatureSnapshot{};
    }

    if (!hw->LockDevice(eAcqContinue)) {
        std::cout << "[TEMP] LockDevice failed" << std::endl;
        return std::nullopt;
    }

    TemperatureSnapshot snapshot;
    bool ok = true;

    for (int board = 0; board < boardCount; ++board) {
        int sensorCount = 0;
        if (!sw->GetTemperatureSensorCount(board, sensorCount)) {
            std::cout << "[TEMP] GetTemperatureSensorCount failed"
                      << " board=" << board
                      << std::endl;
            ok = false;
            break;
        }

        std::cout << "[TEMP] board=" << board
                  << " sensorCount=" << sensorCount
                  << std::endl;

        for (int sensor = 0; sensor < sensorCount; ++sensor) {
            short value = -999;
            const bool okSensor =
                hw->GetTemperatureSensor(board, sensor, &value);

            std::cout << "[TEMP] board=" << board
                      << " sensor=" << sensor
                      << " ok=" << okSensor
                      << " value=" << value
                      << std::endl;

            if (!okSensor) {
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

        short maxValue = -999;
        const bool okMax =
            hw->GetTemperatureMaxHW(board, &maxValue);

        std::cout << "[TEMP_MAX] board=" << board
                  << " ok=" << okMax
                  << " value=" << maxValue
                  << std::endl;

        if (!okMax) {
            ok = false;
            break;
        }

        snapshot.maxPerBoardCelsius.push_back(static_cast<int>(maxValue));
    }

    const bool unlockOk = hw->UnlockDevice();

    std::cout << "[TEMP] UnlockDevice ok=" << unlockOk << std::endl;

    if (!ok || !unlockOk) {
        return std::nullopt;
    }

    return snapshot;
}

} // namespace scanlab::hardware