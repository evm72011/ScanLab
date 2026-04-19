#pragma once

#include <mutex>
#include <vector>

namespace scanlab::acquisition::ascan {

class Cropper
{
public:
    void setMargins(double leftFraction, double rightFraction);
    void disable();

    [[nodiscard]]
    std::vector<float> process(std::vector<float> input) const;

private:
    mutable std::mutex mutex_;
    bool enabled_ = true;
    double leftFraction_ = 0.1;
    double rightFraction_ = 0.5;
};

} // namespace scanlab::acquisition::ascan