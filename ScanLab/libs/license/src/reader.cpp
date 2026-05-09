#include "scanlab/license/reader.h"

#include <fstream>

#include <nlohmann/json.hpp>

namespace scanlab::license
{

Reader::Reader(std::filesystem::path path) : path_{path}
{
}

std::expected<Data, LicenseError> Reader::read() const
{

    if (path_.empty())
    {
        return std::unexpected(LicenseError::LicensePathNotSet);
    }

    std::ifstream file(path_);

    if (!file.is_open())
    {
        return std::unexpected(LicenseError::FileNotFound);
    }

    nlohmann::json json;

    try
    {
        file >> json;
    }
    catch (...)
    {
        return std::unexpected(LicenseError::InvalidJson);
    }

    if (!json.contains("devices") || !json["devices"].is_array() ||
        !json.contains("signature") || !json["signature"].is_string())
    {
        return std::unexpected(LicenseError::InvalidJson);
    }

    try
    {
        return Data{.devices = json["devices"].get<std::vector<std::string>>(),
                    .signatureBase64 = json["signature"].get<std::string>()};
    }
    catch (...)
    {
        return std::unexpected(LicenseError::InvalidDevices);
    }
}

} // namespace scanlab::license