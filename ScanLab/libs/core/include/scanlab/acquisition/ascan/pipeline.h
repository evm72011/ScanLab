#pragma once

#include "scanlab/acquisition/ascan/a_scan_acquisition_source.h"
#include "scanlab/acquisition/ascan/cropper.h"
#include "scanlab/acquisition/ascan/a_scan_frame.h"
#include "scanlab/acquisition/ascan/a_scan_raw_decoder.h"
#include "scanlab/acquisition/ascan/a_scan_resampler.h"

namespace scanlab::acquisition::ascan {

class Pipeline
{
public:
    AScanRawDecoder& decoder();
    const AScanRawDecoder& decoder() const;

    Cropper& cropper();
    const Cropper& cropper() const;

    AScanResampler& resampler();
    const AScanResampler& resampler() const;

    AScanFrame process(const RawAScanFrame& raw) const;

private:
    AScanRawDecoder decoder_;
    Cropper cropper_;
    AScanResampler resampler_;
};

} // namespace scanlab::acquisition::ascan