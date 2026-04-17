#pragma once

namespace scanlab::hardware {
enum class HardwareError
{
    HardwareNotSet,
    OempaInterfaceUnavailable,
    DeviceLockFailed
};
} // namespace scanlab::hardware