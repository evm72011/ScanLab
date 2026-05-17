#pragma once

#include "runtime/errors/describe_error.h"
#include "runtime/errors/describe_error_hw.h"
#include <QHash>

#include "scanlab/config/config_file_error.h"

enum class ConfigFileShellError : uint8_t
{
    InvalidPath,
    DeviceContextNotSet
};

using ConfigError = std::variant<ConfigFileShellError,
    scanlab::device::HardwareError,
    scanlab::config::ConfigFileErrorKind>;

inline ErrorInfo describeError(ConfigFileShellError error)
{
    // clang-format off
    static const QHash<ConfigFileShellError, const char*> descriptions = {
        {ConfigFileShellError::InvalidPath, QT_TR_NOOP("The selected configuration file does not exist or cannot be accessed.")},
        {ConfigFileShellError::DeviceContextNotSet, QT_TR_NOOP("Device context not set")}
    };
    // clang-format on

    return describeErrorImpl(error, descriptions);
}

inline ErrorInfo describeError(scanlab::config::ConfigFileErrorKind error)
{
    using ConfigFileErrorKind = scanlab::config::ConfigFileErrorKind;

    // clang-format off
    static const QHash<ConfigFileErrorKind, const char*> descriptions = {
        {ConfigFileErrorKind::FileNotFound, QT_TR_NOOP("The configuration file was not found.")},
        {ConfigFileErrorKind::LoadFailed, QT_TR_NOOP("Failed to load the configuration file.")},
        {ConfigFileErrorKind::FileCreationFailed, QT_TR_NOOP("Failed to create the configuration file.")},
        {ConfigFileErrorKind::SaveFailed, QT_TR_NOOP("Failed to save the configuration file.")}
    };
    // clang-format on

    return describeErrorImpl(error, descriptions);
}

inline ErrorInfo describeError(const ConfigError& error)
{
    return std::visit([](const auto& value) { return describeError(value); }, error);
}
