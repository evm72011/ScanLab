#pragma once

#include <filesystem>
#include <expected>

#include "license/license_error.h"
#include "license/payload.h"
#include "license/reader.h"

namespace scanlab::license {

template<typename TVerifier>
class Checker {
public:
    explicit Checker(TVerifier verifier)
        : verifier_(std::move(verifier)) {}

    [[nodiscard]]
    std::expected<void, LicenseError> check(const std::filesystem::path& path, std::string_view serialNumber) const {

        auto dataResult = reader_.read(path);

        if (!dataResult.has_value()) {
            return std::unexpected(dataResult.error());
        }

        const auto& data = dataResult.value();

        if (!std::is_sorted(data.devices.begin(), data.devices.end())) {
            return std::unexpected(
                LicenseError::DevicesNotSorted
                );
        }

        const auto payload =
            Payload::fromDevices(data.devices);

        if (!verifier_.verify(payload, data.signatureBase64)) {
            return std::unexpected(
                LicenseError::InvalidSignature
                );
        }

        const auto found = std::binary_search(
            data.devices.begin(),
            data.devices.end(),
            std::string(serialNumber)
            );

        if (!found) {
            return std::unexpected(
                LicenseError::DeviceNotLicensed
                );
        }

        return {};
    }

private:
    Reader reader_;
    TVerifier verifier_;
};

}