#pragma once

/*
enum class DeviceType2 {
    None = 0,
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
*/

#include "runtime/device/device_type_def.h"

enum class DeviceType2 {
#define X(name) name,
    DEVICE_TYPE_LIST(X)
#undef X
};
