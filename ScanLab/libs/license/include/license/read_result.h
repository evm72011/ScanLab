#pragma once

#include <optional>

#include "data.h"
#include "status.h"

namespace license {

struct ReadResult {
    std::optional<Data> data;
    Status status;
};

} // namespace license
