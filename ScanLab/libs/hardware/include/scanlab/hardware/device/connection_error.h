#pragma once

#include <variant>
#include "scanlab/hardware/device/hardware_error.h"

namespace scanlab::hardware {

enum class ConnectionErrorKind {
    AlreadyConnected = 10,
    SetAddressFailure,
    BaseInterfaceUnavailable,
    ConnectionFailure,
    SerialNumberUnavailable
};

using ConnectionError = std::variant<HardwareError,ConnectionErrorKind>;

} // namespace scanlab::hardware

