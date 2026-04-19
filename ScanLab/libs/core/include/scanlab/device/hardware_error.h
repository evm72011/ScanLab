#pragma once

namespace scanlab::hardware {
enum class HardwareError
{
    HardwareNotSet,
    OempaInterfaceUnavailable,
    DeviceLockFailed,
    DeviceUnlockFailed
};
} // namespace scanlab::hardware