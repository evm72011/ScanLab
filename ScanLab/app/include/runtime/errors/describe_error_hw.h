#pragma once

#include <QHash>

#include "runtime/errors/describe_error.h"

#include "scanlab/device/hardware_error.h"
#include "scanlab/device/connection_error.h"


inline ErrorInfo describeError(scanlab::device::HardwareError error)
{
    using HardwareError = scanlab::device::HardwareError;

    static const QHash<HardwareError, const char*> hardwareErrorMap = {
        {HardwareError::HardwareNotSet, QT_TR_NOOP("Hardware is not initialized")},
        {HardwareError::OempaInterfaceUnavailable, QT_TR_NOOP("OEMPA interface is unavailable")},
        {HardwareError::DeviceLockFailed, QT_TR_NOOP("Failed to lock the device")}
    };

    return describeErrorImpl(error, hardwareErrorMap);
}


inline ErrorInfo describeError(scanlab::device::ConnectionErrorKind error)
{
    using ConnectionErrorKind = scanlab::device::ConnectionErrorKind;

    static const QHash<ConnectionErrorKind, const char*> connectionErrorKindMap = {
        {ConnectionErrorKind::AlreadyConnected, QT_TR_NOOP("Device is already connected")},
        {ConnectionErrorKind::SetAddressFailure, QT_TR_NOOP("Failed to set the device address")},
        {ConnectionErrorKind::BaseInterfaceUnavailable, QT_TR_NOOP("Base interface is unavailable")},
        {ConnectionErrorKind::ConnectionFailure, QT_TR_NOOP("Failed to connect to the device")},
        {ConnectionErrorKind::SerialNumberUnavailable, QT_TR_NOOP("Failed to read the serial number")}
    };

    return describeErrorImpl(error, connectionErrorKindMap);
}
