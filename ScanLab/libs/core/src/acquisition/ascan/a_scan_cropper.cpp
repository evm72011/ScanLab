#include "scanlab/acquisition/ascan/a_scan_cropper.h"

#include <algorithm>
#include <vector>

namespace scanlab::acquisition {

void AScanCropper::setRange(int startIndex, int endIndex)
{
    if (startIndex < 0 || endIndex <= startIndex) {
        return;
    }

    std::lock_guard lock(mutex_);
    enabled_ = true;
    startIndex_ = startIndex;
    endIndex_ = endIndex;
}

void AScanCropper::disable()
{
    std::lock_guard lock(mutex_);
    enabled_ = false;
    startIndex_ = 0;
    endIndex_ = 0;
}

std::vector<float> AScanCropper::process(std::vector<float> input) const
{
    bool enabled = false;
    int startIndex = 0;
    int endIndex = 0;

    {
        std::lock_guard lock(mutex_);
        enabled = enabled_;
        startIndex = startIndex_;
        endIndex = endIndex_;
    }

    if (!enabled) {
        return input;
    }

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

} // namespace scanlab::acquisition