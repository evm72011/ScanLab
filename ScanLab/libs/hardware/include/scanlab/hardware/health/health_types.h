#pragma once

namespace scanlab::hardware {

enum class HealthErrorCodes {
    HardwareNotSet,
    OempaInterfaceUnavailable,
    BoardToppologyUnavailable,
    BoardTopologyErrors,
    SensorTopologyUnavailable,
    SensorTopologyErrors,
    DeviceLockFailed,
    SensorDataUnavailable
};

}// namespace scanlab::hardware