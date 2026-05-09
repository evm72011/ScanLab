#pragma once

#include "scanlab/device/device.h"
#include "scanlab/device/hardware_error.h"

#include <expected>
#include <filesystem>
#include <variant>

namespace scanlab::config
{

enum class ConfigFileErrorKind
{
    FileCreationFailed,
    SaveFailed
};

using ConfigFileError =
    std::variant<scanlab::device::HardwareError, ConfigFileErrorKind>;

class FileSaver
{
public:
    explicit FileSaver(scanlab::device::Device &device);

    std::expected<void, ConfigFileError> save(
        const std::filesystem::path &filePath) const;

private:
    scanlab::device::Device &device_;
};

} // namespace scanlab::config
