#include "scanlab/acquisition/ascan/pipeline.h"

#include <utility>

namespace scanlab::acquisition::ascan {

RawDecoder& Pipeline::decoder()
{
    return decoder_;
}

const RawDecoder& Pipeline::decoder() const
{
    return decoder_;
}

Cropper& Pipeline::cropper()
{
    return cropper_;
}

const Cropper& Pipeline::cropper() const
{
    return cropper_;
}

Resampler& Pipeline::resampler()
{
    return resampler_;
}

const Resampler& Pipeline::resampler() const
{
    return resampler_;
}

void Pipeline::setSteps(std::vector<TransformStep> steps)
{
    std::lock_guard lock(stepsMutex_);
    steps_ = std::move(steps);
}

void Pipeline::clearSteps()
{
    std::lock_guard lock(stepsMutex_);
    steps_.clear();
}

Frame Pipeline::process(const RawFrame& raw) const
{
    auto samples = decoder_.decode(raw);

    std::vector<TransformStep> stepsCopy;
    {
        std::lock_guard lock(stepsMutex_);
        stepsCopy = steps_;
    }

    for (const auto step : stepsCopy) {
        switch (step) {
        case TransformStep::Crop:
            samples = cropper_.transform(std::move(samples));
            break;

        case TransformStep::Resample:
            samples = resampler_.transform(std::move(samples));
            break;
        }
    }

    const auto sampleCount = static_cast<int>(samples.size());

    return Frame{
        .samples = std::move(samples),
        .cycle = raw.cycle,
        .dataSize = raw.dataSize,
        .dataCount = sampleCount,
        .bitSize = raw.bitSize,
        .sign = raw.sign
    };
}

} // namespace scanlab::acquisition::ascan