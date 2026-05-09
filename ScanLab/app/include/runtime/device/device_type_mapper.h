#pragma once

#include "runtime/device/device_type.h"
#include "scanlab/device/device_type.h"

static_assert(
    static_cast<int>(DeviceType::None) == static_cast<int>(scanlab::device::DeviceType::Unknown));
static_assert(static_cast<int>(DeviceType::OEMPA_1) ==
              static_cast<int>(scanlab::device::DeviceType::OEMPA_1));
static_assert(static_cast<int>(DeviceType::OEMPA_2) ==
              static_cast<int>(scanlab::device::DeviceType::OEMPA_2));
static_assert(static_cast<int>(DeviceType::OEMPA_Mini) ==
              static_cast<int>(scanlab::device::DeviceType::OEMPA_Mini));
static_assert(static_cast<int>(DeviceType::OEMPA_Max) ==
              static_cast<int>(scanlab::device::DeviceType::OEMPA_Max));
static_assert(static_cast<int>(DeviceType::OEMPA_MC1) ==
              static_cast<int>(scanlab::device::DeviceType::OEMPA_MC1));
static_assert(static_cast<int>(DeviceType::OEMPA_MC2) ==
              static_cast<int>(scanlab::device::DeviceType::OEMPA_MC2));
static_assert(static_cast<int>(DeviceType::OEMPA_MCmu) ==
              static_cast<int>(scanlab::device::DeviceType::OEMPA_MCmu));
static_assert(static_cast<int>(DeviceType::OEMPA_MCmuF) ==
              static_cast<int>(scanlab::device::DeviceType::OEMPA_MCmuF));
static_assert(static_cast<int>(DeviceType::OEMPA_Micro) ==
              static_cast<int>(scanlab::device::DeviceType::OEMPA_Micro));

inline scanlab::device::DeviceType toHardware(DeviceType type)
{
    return static_cast<scanlab::device::DeviceType>(type);
}
