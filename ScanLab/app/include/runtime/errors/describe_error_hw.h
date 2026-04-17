#pragma once

#include <QHash>

#include "runtime/errors/describe_error.h"

#include "scanlab/hardware/device/hardware_error.h"
#include "scanlab/hardware/device/connection_error.h"


namespace hw = scanlab::hardware;

inline ErrorInfo describeError(hw::HardwareError error)
{
    static const QHash<hw::HardwareError, const char*> hardwareErrorMap = {
        {hw::HardwareError::HardwareNotSet, QT_TR_NOOP("Hardware is not initialized")},
        {hw::HardwareError::OempaInterfaceUnavailable, QT_TR_NOOP("OEMPA interface is unavailable")},
        {hw::HardwareError::DeviceLockFailed, QT_TR_NOOP("Failed to lock the device")}
    };

    return describeErrorImpl(error, hardwareErrorMap);
}


inline ErrorInfo describeError(hw::ConnectionErrorKind error)
{
    static const QHash<hw::ConnectionErrorKind, const char*> connectionErrorKindMap = {
        {hw::ConnectionErrorKind::AlreadyConnected, QT_TR_NOOP("Device is already connected")},
        {hw::ConnectionErrorKind::SetAddressFailure, QT_TR_NOOP("Failed to set the device address")},
        {hw::ConnectionErrorKind::BaseInterfaceUnavailable, QT_TR_NOOP("Base interface is unavailable")},
        {hw::ConnectionErrorKind::ConnectionFailure, QT_TR_NOOP("Failed to connect to the device")},
        {hw::ConnectionErrorKind::SerialNumberUnavailable, QT_TR_NOOP("Failed to read the serial number")}
    };

    return describeErrorImpl(error, connectionErrorKindMap);
}
