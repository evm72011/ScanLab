#pragma once

#include "scanlab/hardware/device/connection_error_codes.h"

namespace hw = scanlab::hardware;

enum class ConnectionErrorCodes
{
    DeviceNotSet = -2,
    CreateDeviceFailed = -1,
    HardwareNotSet = 0,
    AlreadyConnected,
    OempaInterfaceUnavailable,
    SetAddressFailure,
    BaseInterfaceUnavailable,
    ConnectionFailure
};


static_assert(static_cast<int>(ConnectionErrorCodes::HardwareNotSet) == static_cast<int>(hw::ConnectionErrorCodes::HardwareNotSet));
static_assert(static_cast<int>(ConnectionErrorCodes::AlreadyConnected) == static_cast<int>(hw::ConnectionErrorCodes::AlreadyConnected));
static_assert(static_cast<int>(ConnectionErrorCodes::OempaInterfaceUnavailable) == static_cast<int>(hw::ConnectionErrorCodes::OempaInterfaceUnavailable));
static_assert(static_cast<int>(ConnectionErrorCodes::SetAddressFailure) == static_cast<int>(hw::ConnectionErrorCodes::SetAddressFailure));
static_assert(static_cast<int>(ConnectionErrorCodes::BaseInterfaceUnavailable) == static_cast<int>(hw::ConnectionErrorCodes::BaseInterfaceUnavailable));
static_assert(static_cast<int>(ConnectionErrorCodes::ConnectionFailure) == static_cast<int>(hw::ConnectionErrorCodes::ConnectionFailure));

inline ConnectionErrorCodes fromHardware(hw::ConnectionErrorCodes code)
{
    return static_cast<ConnectionErrorCodes>(code);
}
