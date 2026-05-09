#include "license/reader.h"

#include <fstream>

#include <nlohmann/json.hpp>
#include <sodium.h>

#include "license/reader.h"

namespace license {
namespace {

using Json = nlohmann::json;

} //namespace

ReadResult Reader::read(const std::filesystem::path& path) const {
    std::ifstream file(path);

    if (!file.is_open()) {
        return { std::nullopt, Status::FileNotFound };
    }

    Json json;

    try {
        file >> json;
    } catch (...) {
        return { std::nullopt, Status::InvalidJson };
    }

    if (!json.contains("devices") ||
        !json["devices"].is_array() ||
        !json.contains("signature") ||
        !json["signature"].is_string()) {
        return { std::nullopt, Status::InvalidJson };
    }

    Data data;

    try {
        data.devices = json["devices"].get<std::vector<std::string>>();
        data.signatureBase64 = json["signature"].get<std::string>();
    } catch (...) {
        return { std::nullopt, Status::InvalidDevices };
    }

    return { std::move(data), Status::Valid };
}

}