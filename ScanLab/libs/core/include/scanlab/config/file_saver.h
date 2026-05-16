#pragma once

#include "scanlab/config/config_file_error.h"
#include "scanlab/device/device.h"

#include <expected>
#include <filesystem>

namespace scanlab::config
{

class FileSaver
{
public:
    explicit FileSaver(scanlab::device::Device& device);

    std::expected<void, ConfigFileError> save(const std::filesystem::path& filePath) const;

private:
    scanlab::device::Device& device_;
};

} // namespace scanlab::config
