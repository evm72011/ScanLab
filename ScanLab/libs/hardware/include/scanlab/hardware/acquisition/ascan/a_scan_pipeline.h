#pragma once

#include "scanlab/hardware/acquisition/ascan/a_scan_acquisition_source.h"
#include "scanlab/hardware/acquisition/ascan/a_scan_frame.h"
#include "scanlab/hardware/acquisition/ascan/a_scan_raw_decoder.h"
#include "scanlab/hardware/acquisition/ascan/a_scan_resampler.h"

namespace scanlab::hardware {

class AScanPipeline
{
public:
    void setTargetSampleCount(int value);

    AScanFrame process(const RawAScanFrame& raw) const;

private:
    AScanRawDecoder decoder_;
    AScanResampler resampler_;
    int targetSampleCount_ = 512;
};

} // namespace scanlab::hardware