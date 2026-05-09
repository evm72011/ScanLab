#pragma once

#include <optional>

#include "data.h"
#include "status.h"

namespace scanlab::license {

struct ReadResult {
    std::optional<Data> data;
    Status status;
};

} // namespace license
