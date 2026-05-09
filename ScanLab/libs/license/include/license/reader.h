#pragma once

#include <filesystem>

#include "read_result.h"

namespace license {

class Reader {
public:
    [[nodiscard]]
    ReadResult read(const std::filesystem::path& path) const;
};

} // namespace license
