#include "scanlab/acquisition/ascan/cropper.h"

#include <algorithm>
#include <cmath>
#include <vector>

namespace scanlab::acquisition::ascan {

void Cropper::setMargins(double leftFraction, double rightFraction)
{
    leftFraction = std::clamp(leftFraction, 0.0, 1.0);
    rightFraction = std::clamp(rightFraction, 0.0, 1.0);

    if (leftFraction + rightFraction >= 1.0) {
        return;
    }

    std::lock_guard lock(mutex_);
    enabled_ = true;
    leftFraction_ = leftFraction;
    rightFraction_ = rightFraction;
}

void Cropper::disable()
{
    std::lock_guard lock(mutex_);
    enabled_ = false;
    leftFraction_ = 0.0;
    rightFraction_ = 0.0;
}

std::vector<float> Cropper::process(std::vector<float> input) const
{
    bool enabled = false;
    double leftFraction = 0.0;
    double rightFraction = 0.0;

    {
        std::lock_guard lock(mutex_);
        enabled = enabled_;
        leftFraction = leftFraction_;
        rightFraction = rightFraction_;
    }

    if (!enabled) {
        return input;
    }

    if (input.empty()) {
        return {};
    }

    const int size = static_cast<int>(input.size());

    const int startIndex =
        std::clamp(static_cast<int>(std::floor(leftFraction * size)), 0, size);

    const int endIndex =
        std::clamp(static_cast<int>(std::ceil((1.0 - rightFraction) * size)), 0, size);

    if (startIndex >= endIndex) {
        return {};
    }

    return std::vector<float>(
        input.begin() + startIndex,
        input.begin() + endIndex);
}

} // namespace scanlab::acquisition::ascan