#include "scanlab/acquisition/ascan/resampler.h"

#include <algorithm>
#include <cstddef>
#include <vector>

namespace scanlab::acquisition::ascan
{

void Resampler::setTargetSampleCount(int value)
{
    std::lock_guard lock(mutex_);
    targetSampleCount_ = value;
}

void Resampler::transform(std::vector<float> &input) const
{
    int targetSampleCount = 0;

    {
        std::lock_guard lock(mutex_);
        targetSampleCount = targetSampleCount_;
    }

    if (input.empty())
    {
        return;
    }

    if (targetSampleCount <= 1)
    {
        return;
    }

    if (static_cast<int>(input.size()) == targetSampleCount)
    {
        return;
    }

    std::vector<float> output(static_cast<std::size_t>(targetSampleCount));

    if (input.size() == 1)
    {
        std::fill(output.begin(), output.end(), input.front());
        input = std::move(output);
        return;
    }

    const int sourceLastIndex = static_cast<int>(input.size()) - 1;
    const int targetLastIndex = targetSampleCount - 1;

    for (int i = 0; i < targetSampleCount; ++i)
    {
        const double position = static_cast<double>(i) *
                                static_cast<double>(sourceLastIndex) /
                                static_cast<double>(targetLastIndex);

        const int leftIndex = static_cast<int>(position);
        const int rightIndex = std::min(leftIndex + 1, sourceLastIndex);
        const double factor = position - static_cast<double>(leftIndex);

        output[static_cast<std::size_t>(i)] = static_cast<float>(
            input[static_cast<std::size_t>(leftIndex)] * (1.0 - factor) +
            input[static_cast<std::size_t>(rightIndex)] * factor);
    }

    input = std::move(output);
}

} // namespace scanlab::acquisition::ascan