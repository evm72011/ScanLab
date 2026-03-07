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

bool Device::connect(const std::wstring& address)
{
    connected_ = true;
    return true;

    if (!device_) {
        return false;
    }

    auto* swOempa = device_->GetSWDeviceOEMPA();
    if (!swOempa || !swOempa->SetAddress(address.c_str())) {
        connected_ = false;
        return false;
    }

    auto* swBase = device_->GetSWDevice();
    if (!swBase || !swBase->SetConnectionState(eConnected, true)) {
        connected_ = false;
        return false;
    }

    connected_ = true;
    return true;
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
}
