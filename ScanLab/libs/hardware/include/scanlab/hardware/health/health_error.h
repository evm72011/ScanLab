#pragma once

#include <variant>
#include "scanlab/hardware/device/hardware_error.h"

namespace scanlab::hardware {

enum class HealthErrorKind {
    BoardToppologyUnavailable,
    BoardTopologyErrors,
    SensorTopologyUnavailable,
    SensorTopologyErrors,
    SensorDataUnavailable
};

using HealthError = std::variant<HardwareError,HealthErrorKind>;

}// namespace scanlab::hardware