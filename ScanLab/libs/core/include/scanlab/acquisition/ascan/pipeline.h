#pragma once

#include "scanlab/acquisition/ascan/acquisition_source.h"
#include "scanlab/acquisition/ascan/cropper.h"
#include "scanlab/acquisition/ascan/frame.h"
#include "scanlab/acquisition/ascan/raw_decoder.h"
#include "scanlab/acquisition/ascan/resampler.h"

namespace scanlab::acquisition::ascan {

class Pipeline
{
public:
    RawDecoder& decoder();
    const RawDecoder& decoder() const;

    Cropper& cropper();
    const Cropper& cropper() const;

    Resampler& resampler();
    const Resampler& resampler() const;

    Frame process(const RawFrame& raw) const;

private:
    RawDecoder decoder_;
    Cropper cropper_;
    Resampler resampler_;
};

} // namespace scanlab::acquisition::ascan