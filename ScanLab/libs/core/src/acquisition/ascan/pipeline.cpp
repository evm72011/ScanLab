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

void Pipeline::addTransformer(Transformer transformer)
{
    if (transformer.isValid()) {
        transformers_.push_back(std::move(transformer));
    }
}

void Pipeline::clearTransformers()
{
    transformers_.clear();
}

Frame Pipeline::process(const RawFrame& raw) const
{
    auto samples = decoder_.decode(raw);

    for (const auto& transformer : transformers_) {
        samples = transformer.transform(std::move(samples));
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