#pragma once

#include "device_type.h"
#include "scanlab/hardware/device_type.h"

namespace hw = scanlab::hardware;

inline hw::DeviceType toHardware(DeviceType::Type type)
{
    switch (type) {

        case DeviceType::OEMPAMax:
            return hw::DeviceType::OEMPAMax;

        case DeviceType::OEMPAMini:
            return hw::DeviceType::OEMPAMini;

        default:
            return hw::DeviceType::Unknown;
    }
}
