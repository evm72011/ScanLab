#pragma once

#include <expected>
#include <filesystem>

#include "scanlab/license/data.h"
#include "scanlab/license/license_error.h"

namespace scanlab::license {

class Reader {
public:
    [[nodiscard]]
    std::expected<Data, LicenseError>
    read(const std::filesystem::path& path) const;
};

} // namespace scanlab::license