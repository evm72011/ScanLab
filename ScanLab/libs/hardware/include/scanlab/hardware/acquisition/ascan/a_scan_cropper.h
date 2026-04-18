#pragma once

#include <vector>

namespace scanlab::hardware {

class AScanCropper
{
public:
    std::vector<float> crop(
        const std::vector<float>& input,
        int startIndex,
        int endIndex) const;
};

} // namespace scanlab::hardware