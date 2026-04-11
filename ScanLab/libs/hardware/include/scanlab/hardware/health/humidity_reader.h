#pragma once

#include "scanlab/hardware/device/device.h"

namespace scanlab::hardware {
class HumidityReader
{
public:
    explicit HumidityReader(Device& device);

private:
    Device& device_;
};
}// namespace scanlab::hardware
