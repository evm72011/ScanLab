#pragma once

#include <mutex>
#include <vector>

namespace scanlab::acquisition::ascan {

class Resampler
{
public:
    void setTargetSampleCount(int value);

    [[nodiscard]]
    std::vector<float> transform(std::vector<float> input) const;

private:
    mutable std::mutex mutex_;
    int targetSampleCount_ = 0;
};

} // namespace scanlab::acquisition::ascan