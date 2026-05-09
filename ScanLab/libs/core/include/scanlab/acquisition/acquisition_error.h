#pragma once

#include "scanlab/device/hardware_error.h"
#include <variant>

namespace scanlab::acquisition
{

enum class AcquisitionErrorKind
{
    ReadParameterFailed,
    WriteParameterFailed,
};

using AcquisitionError = std::variant<scanlab::device::HardwareError, AcquisitionErrorKind>;

} // namespace scanlab::acquisition