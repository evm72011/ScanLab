#pragma once

#include <vector>

namespace scanlab::hardware {

class AScanResampler
{
public:
    std::vector<float> resample(const std::vector<float>& input, int targetSampleCount) const;
};

} // namespace scanlab::hardware