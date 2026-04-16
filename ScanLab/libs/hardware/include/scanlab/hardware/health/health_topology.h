#pragma once
#include <vector>
#include <span>
#include <expected>

#include <Windows.h>
#include <UTDriverOEMPA.h>

#include "scanlab/hardware/health/health_error.h"
#include "scanlab/hardware/health/health_topology_api.h"
#include "scanlab/hardware/device/device.h"


namespace scanlab::hardware {

class HealthTopology
{
public:
    void reset() noexcept;

    template <HealthTopologyApi Api>
    std::expected<void, HealthErrorCodes> ensure(Device& device, const Api& api);

    [[nodiscard]] int boardCount() const noexcept;
    [[nodiscard]] std::span<const int> sensorCountPerBoard() const noexcept;
    [[nodiscard]] std::size_t totalSensorCount() const noexcept;

private:
    CHWDeviceOEMPA* hw_ = nullptr;
    int boardCount_ = 0;
    std::vector<int> sensorCountPerBoard_;
    std::size_t totalSensorCount_ = 0;
};


template <HealthTopologyApi Api>
std::expected<void, HealthErrorCodes> HealthTopology::ensure(Device& device, const Api& api){
    auto* hw = device.get();
    if (hw == nullptr) {
        reset();
        return std::unexpected(HealthErrorCodes::HardwareNotSet);
    }

    if (hw_ == hw) {
        return {};
    }
    reset();

    auto* sw = hw->GetSWDeviceOEMPA();
    if (sw == nullptr) {
        return std::unexpected(HealthErrorCodes::OempaInterfaceUnavailable);
    }

    int boardCount = 0;
    int sensorCountMax = 0;
    std::size_t totalSensorCount = 0;

    if (!api.getBoardCount(sw, boardCount, sensorCountMax)) {
        return std::unexpected(HealthErrorCodes::BoardToppologyUnavailable);
    }

    if (boardCount < 0) {
        return std::unexpected(HealthErrorCodes::BoardTopologyErrors);
    }

    std::vector<int> sensorCountPerBoard;
    sensorCountPerBoard.reserve(static_cast<std::size_t>(boardCount));

    for (int board = 0; board < boardCount; ++board) {
        int sensorCount = 0;
        if (!api.getSensorCount(sw, board, sensorCount)) {
            return std::unexpected(HealthErrorCodes::SensorTopologyUnavailable);
        }

        if (sensorCount < 0) {
            return std::unexpected(HealthErrorCodes::SensorTopologyErrors);
        }

        sensorCountPerBoard.push_back(sensorCount);
        totalSensorCount += static_cast<std::size_t>(sensorCount);
    }

    hw_ = hw;
    boardCount_ = boardCount;
    sensorCountPerBoard_ = std::move(sensorCountPerBoard);
    totalSensorCount_ =totalSensorCount;

    return {};
}
}// namespace scanlab::hardware