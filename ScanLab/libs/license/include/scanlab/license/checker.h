#pragma once

#include <expected>
#include <filesystem>

#include "scanlab/license/license_error.h"
#include "scanlab/license/payload.h"
#include "scanlab/license/reader.h"

namespace scanlab::license
{

template <typename TVerifier>
class Checker
{
public:
    explicit Checker(std::filesystem::path path, TVerifier verifier)
        : reader_(std::move(path)), verifier_(std::move(verifier))
    {
    }

    [[nodiscard]]
    std::expected<void, LicenseError> check(std::string_view serialNumber) const
    {

        auto dataResult = reader_.read();

        if (!dataResult.has_value())
        {
            return std::unexpected(dataResult.error());
        }

        const auto &data = dataResult.value();

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

        const auto found = std::binary_search(data.devices.begin(),
                                              data.devices.end(),
                                              std::string(serialNumber));

        if (!found)
        {
            return std::unexpected(LicenseError::DeviceNotLicensed);
        }

        return {};
    }

private:
    Reader reader_;
    TVerifier verifier_;
};

} // namespace scanlab::license