#pragma once

#include <mutex>
#include <vector>

namespace scanlab::acquisition::ascan
{

class Cropper
{
public:
    void setMargins(double leftFraction, double rightFraction);
    void transform(std::vector<float>& input) const;

private:
    mutable std::mutex mutex_;
    double leftFraction_ = 0.0;
    double rightFraction_ = 0.0;
};

} // namespace scanlab::acquisition::ascan