#pragma once

namespace scanlab::acquisition {

struct AscanParameters {
    int cycle = 0;

    double start = 0.0;
    double range = 0.0;
    int pointCount = 0;
};
} // namespace scanlab::acquisition
