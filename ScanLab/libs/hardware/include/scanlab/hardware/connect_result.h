#pragma once

namespace scanlab::hardware
{

enum class ConnectResult
{
    Success = 0,
    DeviceNotSet,
    AlreadyConnected,
    OempaInterfaceUnavailable,
    SetAddressFailed,
    BaseInterfaceUnavailable,
    ConnectFailed
};

} // namespace scanlab::hardware
