#pragma once

#include "scanlab/hardware/device/connection_error.h"
#include "scanlab/hardware/device/hardware_error.h"

#include "runtime/errors/describe_error.h"
#include "runtime/errors/describe_error_hw.h"
#include "QHash"

namespace hw = scanlab::hardware;

enum class ConnectionLocalError
{
    DeviceContextNotSet,
    CreateDeviceFailed,
};

using ConnectionError = std::variant<
    ConnectionLocalError,
    hw::HardwareError,
    hw::ConnectionErrorKind>;

inline ConnectionError fromHardware(const hw::ConnectionError& error)
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
