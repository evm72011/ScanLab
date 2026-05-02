#pragma once

#include <string>
#include <vector>

namespace scanlab::config {

struct ConfigCycleSnapshot {
    int cycle = 0;
    double start = 0.0;
    double range = 0.0;
    int pointCount = 0;
};

struct ConfigSnapshot {
    std::wstring fileName;
    int cycleCount = 0;
    bool ascanEnabled = false;

    std::vector<ConfigCycleSnapshot> cycles;
};

} // namespace scanlab::config