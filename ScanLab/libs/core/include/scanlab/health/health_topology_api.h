#pragma once

#include <concepts>

class CSWDeviceOEMPA;

namespace scanlab::health {

template <class T>
concept HealthTopologyApi =
    requires(T api, CSWDeviceOEMPA* sw, int& boardCount, int& sensorCountMax, int board, int& sensorCount) {
        { api.getBoardCount(sw, boardCount, sensorCountMax) } -> std::convertible_to<bool>;
        { api.getSensorCount(sw, board, sensorCount) } -> std::convertible_to<bool>;
    };
}// namespace scanlab::hardware