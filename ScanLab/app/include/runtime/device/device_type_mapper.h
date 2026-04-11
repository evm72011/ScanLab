#pragma once

#include "runtime/device/device_type.h"
#include "scanlab/hardware/device/device_type.h"

namespace hw = scanlab::hardware;

static_assert(static_cast<int>(DeviceType2::None) == static_cast<int>(hw::DeviceType::Unknown));
static_assert(static_cast<int>(DeviceType2::OEMPA_1) == static_cast<int>(hw::DeviceType::OEMPA_1));
static_assert(static_cast<int>(DeviceType2::OEMPA_2) == static_cast<int>(hw::DeviceType::OEMPA_2));
static_assert(static_cast<int>(DeviceType2::OEMPA_Mini) == static_cast<int>(hw::DeviceType::OEMPA_Mini));
static_assert(static_cast<int>(DeviceType2::OEMPA_Max) == static_cast<int>(hw::DeviceType::OEMPA_Max));
static_assert(static_cast<int>(DeviceType2::OEMPA_MC1) == static_cast<int>(hw::DeviceType::OEMPA_MC1));
static_assert(static_cast<int>(DeviceType2::OEMPA_MC2) == static_cast<int>(hw::DeviceType::OEMPA_MC2));
static_assert(static_cast<int>(DeviceType2::OEMPA_MCmu) == static_cast<int>(hw::DeviceType::OEMPA_MCmu));
static_assert(static_cast<int>(DeviceType2::OEMPA_MCmuF) == static_cast<int>(hw::DeviceType::OEMPA_MCmuF));
static_assert(static_cast<int>(DeviceType2::OEMPA_Micro) == static_cast<int>(hw::DeviceType::OEMPA_Micro));


inline hw::DeviceType toHardware(DeviceType2 type)
{
    return static_cast<hw::DeviceType>(type);
}
