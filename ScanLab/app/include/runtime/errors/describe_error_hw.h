#pragma once

#include <QHash>

#include "runtime/errors/describe_error.h"

#include "scanlab/device/hardware_error.h"
#include "scanlab/device/connection_error.h"
#include "scanlab/license/license_error.h"


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

inline ErrorInfo describeError(scanlab::license::LicenseError error)
{
    using LicenseError = scanlab::license::LicenseError;

    static const QHash<LicenseError, const char*> licenseErrorKindMap = {
        {LicenseError::LicensePathNotSet, QT_TR_NOOP("License file path is not set.")},
        {LicenseError::FileNotFound, QT_TR_NOOP("License file was not found.")},
        {LicenseError::InvalidJson, QT_TR_NOOP("License file contains invalid JSON.")},
        {LicenseError::InvalidDevices, QT_TR_NOOP("License file contains invalid device data.")},
        {LicenseError::DevicesNotSorted, QT_TR_NOOP("Licensed devices list is not sorted.")},
        {LicenseError::InvalidPublicKey, QT_TR_NOOP("License public key is invalid.")},
        {LicenseError::InvalidSignature, QT_TR_NOOP("License signature verification failed.")},
        {LicenseError::DeviceNotLicensed, QT_TR_NOOP("This device is not covered by the license.")},
        {LicenseError::CryptoInitFailed, QT_TR_NOOP("Cryptographic subsystem initialization failed.")},
    };

    return describeErrorImpl(error, licenseErrorKindMap);
}
