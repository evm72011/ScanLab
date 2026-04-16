#pragma once

namespace scanlab::hardware {
enum class HardwareError
{
    HardwareNotSet = 0,
    OempaInterfaceUnavailable,
    DeviceLockFailed
};
} // namespace scanlab::hardware