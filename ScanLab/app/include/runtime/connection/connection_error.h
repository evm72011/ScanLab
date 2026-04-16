#pragma once

#include "scanlab/hardware/device/connection_error.h"
#include "scanlab/hardware/device/hardware_error.h"

namespace hw = scanlab::hardware;

enum class ConnectionError
{
    DeviceNotSet = -10,
    CreateDeviceFailed,

    HardwareNotSet = 0,
    OempaInterfaceUnavailable,
    DeviceLockFailed,

    AlreadyConnected = 10,
    SetAddressFailure,
    BaseInterfaceUnavailable,
    ConnectionFailure,
    SerialNumberUnavailable
};

static_assert(static_cast<int>(ConnectionError::HardwareNotSet) == static_cast<int>(hw::HardwareError::HardwareNotSet));
static_assert(static_cast<int>(ConnectionError::OempaInterfaceUnavailable) == static_cast<int>(hw::HardwareError::OempaInterfaceUnavailable));
static_assert(static_cast<int>(ConnectionError::DeviceLockFailed) == static_cast<int>(hw::HardwareError::DeviceLockFailed));

static_assert(static_cast<int>(ConnectionError::AlreadyConnected) == static_cast<int>(hw::ConnectionErrorKind::AlreadyConnected));
static_assert(static_cast<int>(ConnectionError::SetAddressFailure) == static_cast<int>(hw::ConnectionErrorKind::SetAddressFailure));
static_assert(static_cast<int>(ConnectionError::BaseInterfaceUnavailable) == static_cast<int>(hw::ConnectionErrorKind::BaseInterfaceUnavailable));
static_assert(static_cast<int>(ConnectionError::ConnectionFailure) == static_cast<int>(hw::ConnectionErrorKind::ConnectionFailure));
static_assert(static_cast<int>(ConnectionError::SerialNumberUnavailable) == static_cast<int>(hw::ConnectionErrorKind::SerialNumberUnavailable));

inline ConnectionError fromHardware(const hw::ConnectionError& code)
{
    return std::visit([](const auto value) {
        return static_cast<ConnectionError>(static_cast<int>(value));
    }, code);
}
