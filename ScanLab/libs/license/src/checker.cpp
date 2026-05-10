#include "scanlab/license/checker.h"
#include "scanlab/license/payload.h"

namespace scanlab::license
{
Checker::Checker(std::filesystem::path path, std::string licensePublicKeyBase64)
    : reader_(std::move(path))
    , verifier_(std::move(licensePublicKeyBase64))
{
}

std::expected<void, LicenseError> Checker::check(std::string_view serialNumber) const
{

    auto dataResult = reader_.read();

    if (!dataResult.has_value())
    {
        return std::unexpected(dataResult.error());
    }

    const auto& data = dataResult.value();

    if (!std::is_sorted(data.devices.begin(), data.devices.end()))
    {
        return std::unexpected(LicenseError::DevicesNotSorted);
    }

    const auto payload = Payload::fromDevices(data.devices);
    auto verifyResult = verifier_.verify(payload, data.signatureBase64);

    if (!verifyResult.has_value())
    {
        return std::unexpected(verifyResult.error());
    }

    const auto found =
        std::binary_search(data.devices.begin(), data.devices.end(), std::string(serialNumber));

    if (!found)
    {
        return std::unexpected(LicenseError::DeviceNotLicensed);
    }

    return {};
}

} // namespace scanlab::license
