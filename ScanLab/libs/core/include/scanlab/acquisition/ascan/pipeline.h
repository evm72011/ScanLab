#pragma once

#include "scanlab/acquisition/ascan/envelope_downsampler.h"
#include "scanlab/acquisition/ascan/frame.h"
#include "scanlab/acquisition/ascan/raw_decoder.h"
#include "scanlab/acquisition/ascan/transformer.h"

#include <mutex>
#include <vector>

namespace scanlab::acquisition::ascan
{

class Pipeline
{
public:
    Frame process(const RawFrame &raw) const;

    RawDecoder &decoder();
    const RawDecoder &decoder() const;

    EnvelopeDownsampler &envelope();
    const EnvelopeDownsampler &envelope() const;

    void setTransformers(std::vector<Transformer> transformers);
    void clearTransformers();

private:
    RawDecoder decoder_;
    EnvelopeDownsampler envelope_;

    mutable std::mutex transformersMutex_;
    std::vector<Transformer> transformers_;
};

} // namespace scanlab::acquisition::ascan