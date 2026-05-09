#pragma once

#include <mutex>
#include <vector>

namespace scanlab::acquisition::ascan
{

class [[deprecated("Use Envelope logic instead")]] Resampler
{
public:
    void setTargetSampleCount(int value);

    void transform(std::vector<float> &input) const;

private:
    mutable std::mutex mutex_;
    int targetSampleCount_ = 0;
};

} // namespace scanlab::acquisition::ascan