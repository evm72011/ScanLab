#pragma once

#include <vector>

namespace scanlab::hardware {

struct AScanFrame
{
    std::vector<float> samples;
    int cycle = 0;
    int dataSize = 0;
    int dataCount = 0;
    int bitSize = 0;
    bool sign = false;
};

} // namespace scanlab::hardware