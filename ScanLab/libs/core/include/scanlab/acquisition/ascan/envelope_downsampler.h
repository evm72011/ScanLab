#pragma once

#include "scanlab/acquisition/ascan/envelope_point.h"

#include <mutex>
#include <vector>

namespace scanlab::acquisition::ascan {

class EnvelopeDownsampler {
public:
    void setTargetPointCount(int value);

    std::vector<EnvelopePoint> transform(const std::vector<float>& input) const;

private:
    mutable std::mutex mutex_;
    int targetPointCount_ = 0;
};

} // namespace scanlab::acquisition::ascan