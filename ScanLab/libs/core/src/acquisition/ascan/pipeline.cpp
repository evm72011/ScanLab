#include "scanlab/acquisition/ascan/pipeline.h"

#include <utility>

namespace scanlab::acquisition::ascan {

AScanRawDecoder& Pipeline::decoder()
{
    return decoder_;
}

const AScanRawDecoder& Pipeline::decoder() const
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

AScanResampler& Pipeline::resampler()
{
    return resampler_;
}

const AScanResampler& Pipeline::resampler() const
{
    return resampler_;
}

AScanFrame Pipeline::process(const RawAScanFrame& raw) const
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

} // namespace scanlab::acquisition::ascan