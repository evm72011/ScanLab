#pragma once

namespace scanlab::device {

enum class HardwareError
{
    HardwareNotSet,
    OempaInterfaceUnavailable,
    DeviceLockFailed,
    DeviceUnlockFailed
};
} // namespace scanlab::hardware