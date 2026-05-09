#pragma once

#include <expected>
#include <filesystem>

#include "license/data.h"
#include "license/license_error.h"

namespace scanlab::license {

class Reader {
public:
    [[nodiscard]]
    std::expected<Data, LicenseError>
    read(const std::filesystem::path& path) const;
};

} // namespace scanlab::license