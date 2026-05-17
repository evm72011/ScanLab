#pragma once

#include "scanlab/device/connection_error.h"
#include "scanlab/device/hardware_error.h"

#include "QHash"
#include "runtime/errors/describe_error.h"
#include "runtime/errors/describe_error_hw.h"

enum class ConnectionShellError : uint8_t
{
    DeviceContextNotSet,
    CreateDeviceFailed,
};

using ConnectionError = std::variant<ConnectionShellError,
    scanlab::device::HardwareError,
    scanlab::device::ConnectionErrorKind,
    scanlab::license::LicenseError>;

inline ConnectionError fromScanlabError(const scanlab::device::ConnectionError& error)
{
    return std::visit([](const auto& value) -> ConnectionError { return value; }, error);
}

inline ErrorInfo describeError(ConnectionShellError error)
{
    static const QHash<ConnectionShellError, const char*> mp = {
        { ConnectionShellError::DeviceContextNotSet, QT_TR_NOOP("Device context is not set") },
        { ConnectionShellError::CreateDeviceFailed, QT_TR_NOOP("Failed to create the device") }
    };

    return describeErrorImpl(error, mp);
}

inline ErrorInfo describeError(const ConnectionError& error)
{
    return std::visit([](const auto& value) { return describeError(value); }, error);
}
