#include "scanlab/acquisition/ascan/cropper.h"

#include <algorithm>
#include <cmath>
#include <vector>

namespace scanlab::acquisition::ascan {

void Cropper::setMargins(double leftFraction, double rightFraction)
{
    std::lock_guard lock(mutex_);

    leftFraction_ = std::clamp(leftFraction, 0.0, 1.0);
    rightFraction_ = std::clamp(rightFraction, 0.0, 1.0);
}

void Cropper::transform(std::vector<float>& samples) const
{
    double leftFraction = 0.0;
    double rightFraction = 0.0;

    {
        std::lock_guard lock(mutex_);
        leftFraction = leftFraction_;
        rightFraction = rightFraction_;
    }

    if (samples.empty()) {
        return;
    }

    if (leftFraction <= 0.0 && rightFraction <= 0.0) {
        return;
    }

    if (leftFraction + rightFraction >= 1.0) {
        samples.clear();
        return;
    }

    const int size = static_cast<int>(samples.size());

    const int startIndex =
        std::clamp(
            static_cast<int>(std::floor(leftFraction * static_cast<double>(size))),
            0,
            size);

    const int endIndex =
        std::clamp(
            static_cast<int>(std::ceil((1.0 - rightFraction) * static_cast<double>(size))),
            0,
            size);

    if (startIndex >= endIndex) {
        samples.clear();
        return;
    }

    samples.erase(samples.begin() + endIndex, samples.end());
    samples.erase(samples.begin(), samples.begin() + startIndex);
}

} // namespace scanlab::acquisition::ascan