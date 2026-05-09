#pragma once

#include "scanlab/device/connection_error.h"
#include "scanlab/device/hardware_error.h"

#include "runtime/errors/describe_error.h"
#include "runtime/errors/describe_error_hw.h"
#include "QHash"

enum class ConnectionLocalError
{
    DeviceContextNotSet,
    CreateDeviceFailed,
};

using ConnectionError = std::variant<
    ConnectionLocalError,
    scanlab::device::HardwareError,
    scanlab::device::ConnectionErrorKind,
    scanlab::license::LicenseError>;

inline ConnectionError fromHardware(const scanlab::device::ConnectionError& error)
{
    return std::visit([](const auto& value) -> ConnectionError {
        return value;
    }, error);
}

inline ErrorInfo describeError(ConnectionLocalError error)
{
    static const QHash<ConnectionLocalError, const char*> mp = {
        {ConnectionLocalError::DeviceContextNotSet, QT_TR_NOOP("Device context is not set")},
        {ConnectionLocalError::CreateDeviceFailed, QT_TR_NOOP("Failed to create the device")}
    };

    return describeErrorImpl(error, mp);
}

inline ErrorInfo describeError(const ConnectionError& error)
{
    return std::visit([](const auto& value) {
        return describeError(value);
    }, error);
}
