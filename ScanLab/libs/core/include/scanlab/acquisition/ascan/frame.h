#pragma once

#include "scanlab/acquisition/ascan/envelope_point.h"

#include <vector>

namespace scanlab::acquisition::ascan {

struct Frame {
    std::vector<EnvelopePoint> samples;
    int cycle = 0;
    int dataSize = 0;
    int dataCount = 0;
    int sourceDataCount = 0;
    int bitSize = 0;
    bool sign = false;
};

} // namespace scanlab::acquisition::ascan
