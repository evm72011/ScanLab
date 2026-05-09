#pragma once

#include "scanlab/config/config_file_error.h"
#include "scanlab/device/device.h"


#include <expected>
#include <filesystem>

namespace scanlab::config
{

class FileLoader
{
public:
    explicit FileLoader(scanlab::device::Device &device);

    std::expected<void, ConfigFileError> load(
        const std::filesystem::path &filePath) const;

private:
    scanlab::device::Device &device_;
};

} // namespace scanlab::config
