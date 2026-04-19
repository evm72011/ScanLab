#pragma once

#include "scanlab/acquisition/ascan/acquisition_source.h"
#include "scanlab/acquisition/ascan/cropper.h"
#include "scanlab/acquisition/ascan/a_scan_frame.h"
#include "scanlab/acquisition/ascan/a_scan_raw_decoder.h"
#include "scanlab/acquisition/ascan/resampler.h"

namespace scanlab::acquisition::ascan {

class Pipeline
{
public:
    AScanRawDecoder& decoder();
    const AScanRawDecoder& decoder() const;

    Cropper& cropper();
    const Cropper& cropper() const;

    Resampler& resampler();
    const Resampler& resampler() const;

    AScanFrame process(const RawFrame& raw) const;

private:
    AScanRawDecoder decoder_;
    Cropper cropper_;
    Resampler resampler_;
};

} // namespace scanlab::acquisition::ascan