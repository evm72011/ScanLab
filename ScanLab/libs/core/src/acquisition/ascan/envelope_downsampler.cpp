#include "scanlab/acquisition/ascan/envelope_downsampler.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>

namespace scanlab::acquisition::ascan {

void EnvelopeDownsampler::setTargetPointCount(int value)
{
    std::lock_guard lock(mutex_);
    targetPointCount_ = std::max(0, value);
}

std::vector<EnvelopePoint> EnvelopeDownsampler::transform(
    const std::vector<float>& input) const
{
    int targetPointCount = 0;

    {
        std::lock_guard lock(mutex_);
        targetPointCount = targetPointCount_;
    }

    if (input.empty()) {
        return {};
    }

    if (targetPointCount <= 0 ||
        static_cast<int>(input.size()) <= targetPointCount) {
        std::vector<EnvelopePoint> output;
        output.reserve(input.size());

        for (float value : input) {
            output.push_back(EnvelopePoint{
                .min = value,
                .max = value
            });
        }

        return output;
    }

    std::vector<EnvelopePoint> output;
    output.reserve(static_cast<std::size_t>(targetPointCount));

    const int sourceCount = static_cast<int>(input.size());

    for (int i = 0; i < targetPointCount; ++i) {
        const int beginIndex = static_cast<int>(
            std::floor(
                static_cast<double>(i) *
                static_cast<double>(sourceCount) /
                static_cast<double>(targetPointCount)));

        const int endIndex = static_cast<int>(
            std::ceil(
                static_cast<double>(i + 1) *
                static_cast<double>(sourceCount) /
                static_cast<double>(targetPointCount)));

        const int begin = std::clamp(beginIndex, 0, sourceCount);
        const int end = std::clamp(endIndex, begin + 1, sourceCount);

        float minValue = std::numeric_limits<float>::max();
        float maxValue = std::numeric_limits<float>::lowest();

        for (int j = begin; j < end; ++j) {
            const float value = input[static_cast<std::size_t>(j)];
            minValue = std::min(minValue, value);
            maxValue = std::max(maxValue, value);
        }

        output.push_back(EnvelopePoint{
            .min = minValue,
            .max = maxValue
        });
    }

    return output;
}

} // namespace scanlab::acquisition::ascan