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

Frame Pipeline::process(const RawFrame& raw) const
{
    auto samples = decoder_.decode(raw);
    samples = cropper_.process(std::move(samples));
    samples = resampler_.process(std::move(samples));

    return Frame {
        .samples = std::move(samples),
        .cycle = raw.cycle,
        .dataSize = raw.dataSize,
        .dataCount = raw.dataCount,
        .bitSize = raw.bitSize,
        .sign = raw.sign
    };
}

} // namespace scanlab::acquisition::ascan