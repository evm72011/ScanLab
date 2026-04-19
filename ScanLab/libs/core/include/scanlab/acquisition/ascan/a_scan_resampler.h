#pragma once

#include <mutex>
#include <vector>

namespace scanlab::acquisition {

class AScanResampler
{
public:
    void setTargetSampleCount(int value);

    std::vector<float> process(std::vector<float> input) const;

private:
    int targetSampleCount_ = 512;
    mutable std::mutex mutex_;
};

} // namespace scanlab::acquisition