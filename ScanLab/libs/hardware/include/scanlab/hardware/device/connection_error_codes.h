#pragma once

namespace scanlab::hardware {

enum class ConnectionErrorCodes {
    HardwareNotSet = 0,
    AlreadyConnected,
    OempaInterfaceUnavailable,
    SetAddressFailure,
    BaseInterfaceUnavailable,
    ConnectionFailure,
    SerialNumberUnavailable
};
} // namespace scanlab::hardware