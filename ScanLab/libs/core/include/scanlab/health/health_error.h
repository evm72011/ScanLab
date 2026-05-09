#pragma once

#include "scanlab/device/hardware_error.h"
#include <variant>

namespace scanlab::health
{

enum class HealthErrorKind
{
    BoardToppologyUnavailable,
    BoardTopologyErrors,
    SensorTopologyUnavailable,
    SensorTopologyErrors,
    SensorDataUnavailable
};

using HealthError = std::variant<scanlab::device::HardwareError, HealthErrorKind>;

} // namespace scanlab::health