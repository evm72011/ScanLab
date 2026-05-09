#pragma once

#include <expected>
#include <filesystem>

#include "scanlab/license/data.h"
#include "scanlab/license/license_error.h"

namespace scanlab::license
{

class Reader
{
public:
    explicit Reader(std::filesystem::path path);

    [[nodiscard]]
    std::expected<Data, LicenseError> read() const;

private:
    std::filesystem::path path_;
};

} // namespace scanlab::license