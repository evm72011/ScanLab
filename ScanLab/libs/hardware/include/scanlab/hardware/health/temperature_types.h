#pragma once

namespace scanlab::hardware {

enum class TemperatureErrorCodes {
    HardwareNotSet,
    OempaInterfaceUnavailable,
    BoardToppologyUnavailable,
    BoardTopologyErrors,
    SensorTopologyUnavailable,
    SensorTopologyErrors,
    DeviceLockFailed,
    MaxBoardTemperatureUnavailable
};

}// namespace scanlab::hardware