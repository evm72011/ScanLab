#pragma once
#include <cstdint>

namespace scanlab::hardware {

enum class DeviceType: uint8_t
{
    Unknown = 0,
    OEMPA_1,
    OEMPA_2,
    OEMPA_Mini,
    OEMPA_Max,
    OEMPA_MC1,
    OEMPA_MC2,
    OEMPA_MCmu,
    OEMPA_MCmuF,
    OEMPA_Micro
};

} // namespace scanlab::hardware
