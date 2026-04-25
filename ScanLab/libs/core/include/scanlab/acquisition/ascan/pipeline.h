#pragma once

#include "scanlab/acquisition/ascan/frame.h"
#include "scanlab/acquisition/ascan/raw_decoder.h"
#include "scanlab/acquisition/ascan/cropper.h"
#include "scanlab/acquisition/ascan/resampler.h"
#include "scanlab/acquisition/ascan/envelope_downsampler.h"

#include <mutex>
#include <vector>

namespace scanlab::acquisition::ascan {

enum class TransformStep
{
    Crop,
    Resample
};

class Pipeline
{
public:
    [[nodiscard]]
    Frame process(const RawFrame& raw) const;

    RawDecoder& decoder();
    const RawDecoder& decoder() const;

    Cropper& cropper();
    const Cropper& cropper() const;

    Resampler& resampler();
    const Resampler& resampler() const;

    EnvelopeDownsampler& envelope();
    const EnvelopeDownsampler& envelope() const;

    void setSteps(std::vector<TransformStep> steps);
    void clearSteps();

private:
    RawDecoder decoder_;
    Cropper cropper_;
    Resampler resampler_;
    EnvelopeDownsampler envelope_;

    mutable std::mutex stepsMutex_;
    std::vector<TransformStep> steps_;
};

} // namespace scanlab::acquisition::ascan