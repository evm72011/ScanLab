#include "runtime/config/config_file_service.h"
#include "runtime/device/device_context.h"

#include <QFileInfo>

#include "scanlab/config/file_loader.h"

namespace sc = scanlab::config;

ConfigFileService::ConfigFileService(DeviceContext& context)
    : context_(context)
{
}


std::expected<void, ConfigFileError> ConfigFileService::loadToHardware(const QString& fileName)
{
    QFileInfo info(fileName);

    if (!info.exists() || !info.isFile() || !info.isReadable())
    {
        return std::unexpected(ConfigFileError::InvalidPath);
    }

    auto* device = context_.device();
    if (!device)
    {
        return std::unexpected(ConfigFileError::HardwareNotSet);
    }

    sc::FileLoader loader(*device);

    const auto result =
        loader.load(info.canonicalFilePath().toStdString());

    if (!result.has_value())
    {
        return std::unexpected(ConfigFileError::LoadFailed);
    }

    return {};
}

std::expected<void, ConfigFileError> ConfigFileService::saveFromHardware(const QString& fileName)
{
    return {};
}