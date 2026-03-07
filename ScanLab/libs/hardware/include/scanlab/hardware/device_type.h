#pragma once
#include <cstdint>

namespace scanlab::hardware {

enum class DeviceType: uint8_t
{
    Unknown = 0,
    OEMPAMax,
    OEMPAMini
};

} // namespace scanlab::hardware
