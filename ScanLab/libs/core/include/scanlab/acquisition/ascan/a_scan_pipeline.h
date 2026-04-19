#pragma once

#include "scanlab/acquisition/ascan/a_scan_acquisition_source.h"
#include "scanlab/acquisition/ascan/a_scan_cropper.h"
#include "scanlab/acquisition/ascan/a_scan_frame.h"
#include "scanlab/acquisition/ascan/a_scan_raw_decoder.h"
#include "scanlab/acquisition/ascan/a_scan_resampler.h"

namespace scanlab::hardware {

class AScanPipeline
{
public:
    AScanRawDecoder& decoder();
    const AScanRawDecoder& decoder() const;

    AScanCropper& cropper();
    const AScanCropper& cropper() const;

    AScanResampler& resampler();
    const AScanResampler& resampler() const;

    AScanFrame process(const RawAScanFrame& raw) const;

private:
    AScanRawDecoder decoder_;
    AScanCropper cropper_;
    AScanResampler resampler_;
};

} // namespace scanlab::hardware