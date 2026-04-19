#pragma once

#include <variant>
#include "scanlab/device/hardware_error.h"

namespace scanlab::health {

enum class HealthErrorKind {
    BoardToppologyUnavailable,
    BoardTopologyErrors,
    SensorTopologyUnavailable,
    SensorTopologyErrors,
    SensorDataUnavailable
};

using HealthError = std::variant<scanlab::device::HardwareError,HealthErrorKind>;

}// namespace scanlab::health