#include "scanlab/hardware/device.h"

#include <memory>

#include <UTDriverOEMPA.h>
#include <UTDriverOEMPAmax.h>

namespace scanlab::hardware {


Device::Device() = default;
Device::~Device() = default;

Device::Device(Device&&) noexcept = default;
Device& Device::operator=(Device&&) noexcept = default;

bool Device::setDevice(DeviceType type)
{
    disconnect();

    switch (type) {
    case DeviceType::OEMPAMax:
        device_ = std::make_unique<CHWDeviceOEMPAmax>();
        break;

    case DeviceType::OEMPAMini:
        device_ = std::make_unique<CHWDeviceOEMPAmini>();
        break;

    default:
        device_.reset();
        return false;
    }

    connected_ = false;
    return true;
}

ConnectResult Device::connect(const std::wstring& address)
{
    if (!device_) {
        return ConnectResult::DeviceNotSet;
    }

    if (connected_) {
        return ConnectResult::AlreadyConnected;
    }

    auto* swOempa = device_->GetSWDeviceOEMPA();
    if (!swOempa) {
        return ConnectResult::OempaInterfaceUnavailable;
    }

    if (!swOempa->SetAddress(address.c_str())) {
        return ConnectResult::SetAddressFailed;
    }

    auto* swBase = device_->GetSWDevice();
    if (!swBase) {
        return ConnectResult::BaseInterfaceUnavailable;
    }

    if (!swBase->SetConnectionState(eConnected, true)) {
        return ConnectResult::ConnectFailed;
    }

    connected_ = true;
    return ConnectResult::Success;
}

void Device::disconnect()
{
    if (device_) {
        if (auto* swBase = device_->GetSWDevice()) {
            swBase->SetConnectionState(eConnected, false);
        }
    }

    connected_ = false;
}

bool Device::hasDevice() const
{
    return static_cast<bool>(device_);
}

bool Device::isConnected() const
{
    return connected_;
}

CHWDeviceOEMPA* Device::get()
{
    return device_.get();
}

const CHWDeviceOEMPA* Device::get() const
{
    return device_.get();
}

} // namespace scanlab::hardware
