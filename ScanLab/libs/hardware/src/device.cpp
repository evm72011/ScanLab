#include "scanlab/hardware/device.h"

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

bool Device::setDevice(DeviceType type)
{
    disconnect();

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


/*
 *	if (m_pHWDeviceOEMPA)
        delete m_pHWDeviceOEMPA;

    switch (m_iComboDeviceType)
    {
    case 0:
    case 1:
        m_pHWDeviceOEMPA = new CHWDeviceOEMPA1;
        break;
    case 2:
        m_pHWDeviceOEMPA = new CHWDeviceOEMPA2;
        break;
    case 3:
        m_pHWDeviceOEMPA = new CHWDeviceOEMPAmini;
        break;
    case 4:
        m_pHWDeviceOEMPA = new CHWDeviceOEMPAmax;
        break;
    case 5:
        m_pHWDeviceOEMPA = new CHWDeviceOEMMC2;
        break;
    case 6:
        m_pHWDeviceOEMPA = new CHWDeviceOEMMCu;
        break;
    case 7:
        m_pHWDeviceOEMPA = new CHWDeviceOEMMCuF;
        break;
    case 8:
        m_pHWDeviceOEMPA = new CHWDeviceOEMPAmicro;
        break;
    }
    InitHardware();
    UpdateDialog();
 */