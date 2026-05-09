#pragma once
#include <expected>
#include <span>
#include <vector>

#include "scanlab/oempa/sdk.h" // IWYU pragma: keep

#include "scanlab/device/device.h"
#include "scanlab/health/health_error.h"
#include "scanlab/health/health_topology_api.h"

namespace scanlab::health
{

class HealthTopology
{
public:
    void reset() noexcept;

    template <HealthTopologyApi Api>
    std::expected<void, HealthError> ensure(scanlab::device::Device& device, const Api& api);

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
std::expected<void, HealthError> HealthTopology::ensure(scanlab::device::Device& device,
    const Api& api)
{
    auto* hw = device.get();
    if (hw == nullptr)
    {
        reset();
        return std::unexpected(scanlab::device::HardwareError::HardwareNotSet);
    }

    if (hw_ == hw)
    {
        return {};
    }
    reset();

    auto* sw = hw->GetSWDeviceOEMPA();
    if (sw == nullptr)
    {
        return std::unexpected(scanlab::device::HardwareError::OempaInterfaceUnavailable);
    }

    int boardCount = 0;
    int sensorCountMax = 0;
    std::size_t totalSensorCount = 0;

    if (!api.getBoardCount(sw, boardCount, sensorCountMax))
    {
        return std::unexpected(HealthErrorKind::BoardToppologyUnavailable);
    }

    if (boardCount < 0)
    {
        return std::unexpected(HealthErrorKind::BoardTopologyErrors);
    }

    std::vector<int> sensorCountPerBoard;
    sensorCountPerBoard.reserve(static_cast<std::size_t>(boardCount));

    for (int board = 0; board < boardCount; ++board)
    {
        int sensorCount = 0;
        if (!api.getSensorCount(sw, board, sensorCount))
        {
            return std::unexpected(HealthErrorKind::SensorTopologyUnavailable);
        }

        if (sensorCount < 0)
        {
            return std::unexpected(HealthErrorKind::SensorTopologyErrors);
        }

        sensorCountPerBoard.push_back(sensorCount);
        totalSensorCount += static_cast<std::size_t>(sensorCount);
    }

    hw_ = hw;
    boardCount_ = boardCount;
    sensorCountPerBoard_ = std::move(sensorCountPerBoard);
    totalSensorCount_ = totalSensorCount;

    return {};
}
} // namespace scanlab::health