#include "scanlab/hardware/acquisition/ascan/a_scan_pipeline.h"

namespace scanlab::hardware {

void AScanPipeline::setTargetSampleCount(int value)
{
    if (value < 2) {
        return;
    }

    targetSampleCount_ = value;
}

AScanFrame AScanPipeline::process(const RawAScanFrame& raw) const
{
    auto samples = decoder_.decode(raw);
    samples = resampler_.resample(samples, targetSampleCount_);

    AScanFrame frame;
    frame.samples = std::move(samples);
    frame.cycle = raw.cycle;
    frame.dataSize = raw.dataSize;
    frame.dataCount = raw.dataCount;
    frame.bitSize = raw.bitSize;
    frame.sign = raw.sign;

    return frame;
}

} // namespace scanlab::hardware