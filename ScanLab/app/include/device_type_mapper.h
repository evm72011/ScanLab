#pragma once

#include "device_type.h"
#include "scanlab/hardware/device_type.h"

namespace hw = scanlab::hardware;

static_assert(static_cast<int>(DeviceType::None) == static_cast<int>(hw::DeviceType::Unknown));
static_assert(static_cast<int>(DeviceType::OEMPA_1) == static_cast<int>(hw::DeviceType::OEMPA_1));
static_assert(static_cast<int>(DeviceType::OEMPA_2) == static_cast<int>(hw::DeviceType::OEMPA_2));
static_assert(static_cast<int>(DeviceType::OEMPA_Mini) == static_cast<int>(hw::DeviceType::OEMPA_Mini));
static_assert(static_cast<int>(DeviceType::OEMPA_Max) == static_cast<int>(hw::DeviceType::OEMPA_Max));
static_assert(static_cast<int>(DeviceType::OEMPA_MC1) == static_cast<int>(hw::DeviceType::OEMPA_MC1));
static_assert(static_cast<int>(DeviceType::OEMPA_MC2) == static_cast<int>(hw::DeviceType::OEMPA_MC2));
static_assert(static_cast<int>(DeviceType::OEMPA_MCmu) == static_cast<int>(hw::DeviceType::OEMPA_MCmu));
static_assert(static_cast<int>(DeviceType::OEMPA_MCmuF) == static_cast<int>(hw::DeviceType::OEMPA_MCmuF));
static_assert(static_cast<int>(DeviceType::OEMPA_Micro) == static_cast<int>(hw::DeviceType::OEMPA_Micro));


inline hw::DeviceType toHardware(DeviceType::Type type)
{
    return static_cast<hw::DeviceType>(type);
}
