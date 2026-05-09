#pragma once

#include <variant>
#include "scanlab/device/hardware_error.h"
#include "license/status.h"

namespace scanlab::device {

enum class ConnectionErrorKind {
    AlreadyConnected,
    SetAddressFailure,
    BaseInterfaceUnavailable,
    ConnectionFailure,
    SerialNumberUnavailable
};

using ConnectionError = std::variant<
    HardwareError,
    ConnectionErrorKind,
    license::Status>;

} // namespace scanlab::device

