#pragma once

#include <variant>
#include "scanlab/device/hardware_error.h"

namespace scanlab::hardware {

enum class AcquisitionErrorKind {
    Foo,
};

using AcquisitionError = std::variant<scanlab::device::HardwareError,AcquisitionErrorKind>;

} // namespace scanlab::hardware