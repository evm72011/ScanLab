#include "scanlab/acquisition/ascan/pipeline.h"

#include <utility>

namespace scanlab::acquisition::ascan
{

RawDecoder &Pipeline::decoder()
{
    return decoder_;
}

const RawDecoder &Pipeline::decoder() const
{
    return decoder_;
}

EnvelopeDownsampler &Pipeline::envelope()
{
    return envelope_;
}

const EnvelopeDownsampler &Pipeline::envelope() const
{
    return envelope_;
}

void Pipeline::setTransformers(std::vector<Transformer> transformers)
{
    std::lock_guard lock(transformersMutex_);
    transformers_ = std::move(transformers);
}

void Pipeline::clearTransformers()
{
    std::lock_guard lock(transformersMutex_);
    transformers_.clear();
}

Frame Pipeline::process(const RawFrame &raw) const
{
    auto samples = decoder_.decode(raw);

    std::vector<Transformer> transformersCopy;
    {
        std::lock_guard lock(transformersMutex_);
        transformersCopy = transformers_;
    }

    for (const auto &transformer : transformersCopy)
    {
        transformer.transform(samples);
    }

    auto envelopeSamples = envelope_.transform(samples);

    const auto displayCount = static_cast<int>(envelopeSamples.size());
    const auto sourceCount = static_cast<int>(samples.size());

    return Frame{.samples = std::move(envelopeSamples),
                 .cycle = raw.cycle,
                 .dataSize = raw.dataSize,
                 .dataCount = displayCount,
                 .sourceDataCount = sourceCount,
                 .bitSize = raw.bitSize,
                 .sign = raw.sign};
}

} // namespace scanlab::acquisition::ascan