#pragma once

#include <mutex>
#include <vector>

namespace scanlab::acquisition {

class AScanCropper
{
public:
    void setRange(int startIndex, int endIndex);
    void disable();

    std::vector<float> process(std::vector<float> input) const;

private:
    bool enabled_ = false;
    int startIndex_ = 0;
    int endIndex_ = 0;
    mutable std::mutex mutex_;
};

} // namespace scanlab::acquisition