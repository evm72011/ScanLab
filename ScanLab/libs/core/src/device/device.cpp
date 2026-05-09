#include "scanlab/device/device.h"

#include <array>
#include <memory>

#include <UTDriverOEMPA1.h>
#include <UTDriverOEMPA2.h>

#include <UTDriverOEMMC.h>
#include <UTDriverOEMPA.h>
#include <UTDriverOEMPAmax.h>
#include <UTDriverOEMPAmicro.h>

#include "scanlab/device/hardware_error.h"

#include "scanlab/license/ed25519_verifier.h"

namespace scanlab::device
{

using Ed25519Verifier = scanlab::license::Ed25519Verifier;

Device::Device(std::filesystem::path licensePath,
               std::string licensePublicKeyBase64)
    : licenseChecker_(std::move(licensePath),
                      Ed25519Verifier(std::move(licensePublicKeyBase64)))
{
}

Device::Device(Device &&) noexcept = default;
Device &Device::operator=(Device &&) noexcept = default;

std::expected<ConnectionResult, ConnectionError> Device::connect(
    const std::wstring &address)
{
    if (!device_)
    {
        return std::unexpected(HardwareError::HardwareNotSet);
    }

    if (isConnected())
    {
        return std::unexpected(ConnectionErrorKind::AlreadyConnected);
    }

    auto *swOempa = device_->GetSWDeviceOEMPA();
    if (!swOempa)
    {
        return std::unexpected(HardwareError::OempaInterfaceUnavailable);
    }

    if (!swOempa->SetAddress(address.c_str()))
    {
        return std::unexpected(ConnectionErrorKind::SetAddressFailure);
    }

    auto *swBase = device_->GetSWDevice();
    if (!swBase)
    {
        return std::unexpected(ConnectionErrorKind::BaseInterfaceUnavailable);
    }

    if (!swBase->SetConnectionState(eConnected, true))
    {
        return std::unexpected(ConnectionErrorKind::ConnectionFailure);
    }

    std::array<wchar_t, 64> serialBuffer{};
    if (!swOempa->GetSerialNumber(serialBuffer.data(),
                                  static_cast<int>(serialBuffer.size())))
    {
        return std::unexpected(ConnectionErrorKind::SerialNumberUnavailable);
    }

    const std::wstring serial(serialBuffer.data());

    const auto licenseResult =
        licenseChecker_.check(std::string(serial.begin(), serial.end()));

    if (!licenseResult)
    {
        disconnect();
        return std::unexpected(licenseResult.error());
    }

    return ConnectionResult{serial};
}

bool Device::disconnect()
{
    if (!isConnected())
    {
        return true;
    }

    auto *swBase = device_->GetSWDevice();
    if (!swBase)
    {
        return false;
    }

    auto result = swBase->SetConnectionState(eDisconnected, true);
    return result;
}

bool Device::ensureDevice(DeviceType type)
{
    if (device_ && type_ == type)
    {
        return true;
    }

    if (isConnected())
    {
        disconnect();
    }

    device_.reset();

    switch (type)
    {
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

bool Device::hasDevice() const
{
    return static_cast<bool>(device_);
}

bool Device::isConnected() const
{
    if (!device_)
    {
        return false;
    }

    auto *swBase = device_->GetSWDevice();
    return swBase && swBase->IsConnected();
}

CHWDeviceOEMPA *Device::get()
{
    return device_.get();
}

const CHWDeviceOEMPA *Device::get() const
{
    return device_.get();
}
} // namespace scanlab::device
