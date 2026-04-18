#include "scanlab/hardware/acquisition/ascan/a_scan_cropper.h"

#include <algorithm>
#include <vector>

namespace scanlab::hardware {

std::vector<float> AScanCropper::crop(
    const std::vector<float>& input,
    int startIndex,
    int endIndex) const
{
    if (input.empty()) {
        return {};
    }

    const int size = static_cast<int>(input.size());

    startIndex = std::max(0, startIndex);
    endIndex = std::min(endIndex, size);

    if (startIndex >= endIndex) {
        return {};
    }

    return std::vector<float>(
        input.begin() + startIndex,
        input.begin() + endIndex);
}

} // namespace scanlab::hardware