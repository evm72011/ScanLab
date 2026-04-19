#include "scanlab/acquisition/ascan/a_scan_pipeline.h"

#include <utility>

namespace scanlab::hardware {

AScanRawDecoder& AScanPipeline::decoder()
{
    return decoder_;
}

const AScanRawDecoder& AScanPipeline::decoder() const
{
    return decoder_;
}

AScanCropper& AScanPipeline::cropper()
{
    return cropper_;
}

const AScanCropper& AScanPipeline::cropper() const
{
    return cropper_;
}

AScanResampler& AScanPipeline::resampler()
{
    return resampler_;
}

const AScanResampler& AScanPipeline::resampler() const
{
    return resampler_;
}

AScanFrame AScanPipeline::process(const RawAScanFrame& raw) const
{
    auto samples = decoder_.decode(raw);
    samples = cropper_.process(std::move(samples));
    samples = resampler_.process(std::move(samples));

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