#pragma once

#include <variant>
#include "scanlab/hardware/device/hardware_error.h"

namespace scanlab::hardware {

enum class AcquisitionErrorKind {
    Foo,
};

using AcquisitionError = std::variant<HardwareError,AcquisitionErrorKind>;

} // namespace scanlab::hardware