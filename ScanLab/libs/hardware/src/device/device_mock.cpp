#include "scanlab/hardware/device/device.h"

#include <array>
#include <memory>

#include <UTDriverOEMPA1.h>
#include <UTDriverOEMPA2.h>

#include <UTDriverOEMPA.h>
#include <UTDriverOEMPAmax.h>
#include <UTDriverOEMMC.h>
#include <UTDriverOEMPAmicro.h>

namespace scanlab::hardware {


Device::Device() = default;
Device::~Device() = default;

Device::Device(Device&&) noexcept = default;
Device& Device::operator=(Device&&) noexcept = default;

std::expected<ConnectionResult,ConnectionErrorCodes> Device::connect(const std::wstring& address)
{
    if (!device_) {
        return std::unexpected(ConnectionErrorCodes::HardwareNotSet);
    }

    if (isConnected()) {
        return std::unexpected(ConnectionErrorCodes::AlreadyConnected);
    }

    connected_ = true;
    return ConnectionResult{
        L"MOCK:" + address
    };
}

bool Device::ensureDevice(DeviceType type) {        // TODO simplify in mock
    if (device_ && type_ == type) {
        return true;
    }

    if (isConnected()) {
        disconnect();
    }

    device_.reset();

    switch (type) {
    case DeviceType::OEMPA_1:
        device_ = std::make_unique<CHWDeviceOEMPA1>();
        break;
    case DeviceType::OEMPA_2:
        device_ = std::make_unique<CHWDeviceOEMPA2>();
        break;
    case DeviceType::OEMPA_Mini:
        device_ = std::make_unique<CHWDeviceOEMPAmini>();
        break;
    case DeviceType::OEMPA_Max:
        device_ = std::make_unique<CHWDeviceOEMPAmax>();
        break;
    case DeviceType::OEMPA_MC1:
        device_ = std::make_unique<CHWDeviceOEMPA1>();
        break;
    case DeviceType::OEMPA_MC2:
        device_ = std::make_unique<CHWDeviceOEMMC2>();
        break;
    case DeviceType::OEMPA_MCmu:
        device_ = std::make_unique<CHWDeviceOEMMCu>();
        break;
    case DeviceType::OEMPA_MCmuF:
        device_ = std::make_unique<CHWDeviceOEMMCuF>();
        break;
    case DeviceType::OEMPA_Micro:
        device_ = std::make_unique<CHWDeviceOEMPAmicro>();
        break;
    default:
        device_.reset();
        type_.reset();
        return false;
    }

    type_ = type;
    return true;
}

bool Device::disconnect()
{
    connected_ = false;
    return true;
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
