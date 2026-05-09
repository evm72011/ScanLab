#pragma once

#include "scanlab/device/hardware_error.h"
#include <variant>

namespace scanlab::config
{

enum class ConfigFileErrorKind
{
    FileNotFound,
    LoadFailed,
    FileCreationFailed,
    SaveFailed
};

using ConfigFileError =
    std::variant<scanlab::device::HardwareError, ConfigFileErrorKind>;

} // namespace scanlab::config
