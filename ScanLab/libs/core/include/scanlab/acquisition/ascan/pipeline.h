#pragma once

#include "scanlab/acquisition/ascan/frame.h"
#include "scanlab/acquisition/ascan/raw_decoder.h"
#include "scanlab/acquisition/ascan/transformer.h"

#include <vector>

namespace scanlab::acquisition::ascan {

class Pipeline
{
public:
    [[nodiscard]]
    Frame process(const RawFrame& raw) const;

    RawDecoder& decoder();
    const RawDecoder& decoder() const;

    void addTransformer(Transformer transformer);
    void clearTransformers();

private:
    RawDecoder decoder_;
    std::vector<Transformer> transformers_;
};

} // namespace scanlab::acquisition::ascan