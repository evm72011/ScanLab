#include "scanlab/device/device.h"

#include <memory>

#include "scanlab/device/hardware_error.h"
#include "scanlab/license/ed25519_verifier.h"

namespace scanlab::device
{

using Ed25519Verifier = scanlab::license::Ed25519Verifier;

Device::Device(std::filesystem::path licensePath, std::string licensePublicKeyBase64)
    : licenseChecker_(std::move(licensePath), std::move(licensePublicKeyBase64))
{
}

Device::Device(Device&&) noexcept = default;
Device& Device::operator=(Device&&) noexcept = default;

std::expected<ConnectionResult, ConnectionError> Device::connect(
    [[maybe_unused]] const std::wstring& address)
{
    if (!type_)
    {
        return std::unexpected(HardwareError::HardwareNotSet);
    }

    if (isConnected())
    {
        return std::unexpected(ConnectionErrorKind::AlreadyConnected);
    }

    const auto serial = std::string("MOCK_12345");

    const auto licenseResult = licenseChecker_.check(serial);
    if (!licenseResult)
    {
        disconnect();
        return std::unexpected(licenseResult.error());
    }

    connected_ = true;
    return ConnectionResult{ std::wstring(serial.begin(), serial.end()) };
}

bool Device::ensureDevice(DeviceType type)
{
    if (type_ == type)
    {
        return true;
    }

    if (isConnected())
    {
        disconnect();
    }

    device_.reset();
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
    return type_.has_value();
}

bool Device::isConnected() const
{
    return connected_;
}

CHWDeviceOEMPA* Device::get()
{
    return nullptr;
}

const CHWDeviceOEMPA* Device::get() const
{
    return device_.get();
}
} // namespace scanlab::device
