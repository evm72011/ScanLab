#pragma once

#include <variant>
#include "scanlab/device/hardware_error.h"
#include "scanlab/license/license_error.h"

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
    scanlab::license::LicenseError>;

} // namespace scanlab::device

