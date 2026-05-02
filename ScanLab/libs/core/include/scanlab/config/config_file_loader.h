#pragma once

#include "scanlab/device/device.h"
#include "scanlab/config/config_file_error.h"


#include <expected>
#include <filesystem>

namespace scanlab::config {

class ConfigFileLoader {
public:
    explicit ConfigFileLoader(scanlab::device::Device& device);

    std::expected<void, ConfigFileError>
    load(const std::filesystem::path& filePath) const;

private:
    scanlab::device::Device& device_;
};

} // namespace scanlab::config
