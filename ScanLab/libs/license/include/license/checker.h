#pragma once

#include <filesystem>

#include "check_result.h"
#include "payload.h"
#include "reader.h"

namespace license {

template<typename TVerifier>
class Checker {
public:
    explicit Checker(TVerifier verifier)
        : verifier_(std::move(verifier)) {}

    [[nodiscard]]
    CheckResult check(
        const std::filesystem::path& path,
        std::string_view serialNumber
        ) const {
        if (!verifier_.isReady()) {
            return { false, verifier_.status() };
        }

        const auto readResult = reader_.read(path);

        if (!readResult.data.has_value()) {
            return { false, readResult.status };
        }

        const auto& data = *readResult.data;

        if (!std::is_sorted(data.devices.begin(), data.devices.end())) {
            return { false, Status::DevicesNotSorted };
        }

        const auto payload = Payload::fromDevices(data.devices);

        if (!verifier_.verify(payload, data.signatureBase64)) {
            return { false, Status::InvalidSignature };
        }

        const auto found = std::binary_search(
            data.devices.begin(),
            data.devices.end(),
            std::string(serialNumber)
            );

        if (!found) {
            return { false, Status::DeviceNotLicensed };
        }

        return { true, Status::Valid };
    }

private:
    Reader reader_;
    TVerifier verifier_;
};

}