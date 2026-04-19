#pragma once

#include "scanlab/acquisition/ascan/acquisition_source.h"
#include "scanlab/acquisition/ascan/cropper.h"
#include "scanlab/acquisition/ascan/frame.h"
#include "scanlab/acquisition/ascan/raw_decoder.h"
#include "scanlab/acquisition/ascan/resampler.h"

namespace scanlab::acquisition::ascan {

struct PipelineConfig {
    bool cropEnabled = true;
    bool resampleEnabled = true;
};

class Pipeline
{
public:
    PipelineConfig& config() { return config_; }
    const PipelineConfig& config() const { return config_; }

    Frame process(const RawFrame& raw) const;

    RawDecoder& decoder();
    const RawDecoder& decoder() const;

    Cropper& cropper();
    const Cropper& cropper() const;

    Resampler& resampler();
    const Resampler& resampler() const;

private:
    PipelineConfig config_;
    RawDecoder decoder_;
    Cropper cropper_;
    Resampler resampler_;
};

} // namespace scanlab::acquisition::ascan