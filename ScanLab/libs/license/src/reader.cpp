#include "scanlab/license/reader.h"

#include <fstream>

#include <nlohmann/json.hpp>

namespace scanlab::license {

namespace {

using Json = nlohmann::json;

} // namespace

std::expected<Data, LicenseError>
Reader::read(const std::filesystem::path& path) const {
    std::ifstream file(path);

    if (!file.is_open()) {
        return std::unexpected(
            LicenseError::FileNotFound
            );
    }

    Json json;

    try {
        file >> json;
    } catch (...) {
        return std::unexpected(
            LicenseError::InvalidJson
            );
    }

    if (!json.contains("devices") ||
        !json["devices"].is_array() ||
        !json.contains("signature") ||
        !json["signature"].is_string()) {
        return std::unexpected(
            LicenseError::InvalidJson
            );
    }

    Data data;

    try {
        data.devices =
            json["devices"]
                .get<std::vector<std::string>>();

        data.signatureBase64 =
            json["signature"]
                .get<std::string>();
    } catch (...) {
        return std::unexpected(
            LicenseError::InvalidDevices
            );
    }

    return data;
}

} // namespace scanlab::license