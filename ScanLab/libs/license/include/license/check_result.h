#pragma once

#include "status.h"

namespace license {

struct CheckResult {
    bool allowed;
    Status status;
};

} // namespace license
