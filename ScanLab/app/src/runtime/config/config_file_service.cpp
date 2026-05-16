#include "runtime/config/config_file_service.h"
#include "runtime/device/device_context.h"

#include <QFileInfo>

#include "scanlab/config/file_loader.h"
#include "scanlab/config/file_saver.h"

namespace sc = scanlab::config;

ConfigFileService::ConfigFileService(DeviceContext& context)
    : context_(context)
{
}

std::expected<void, ConfigError> ConfigFileService::loadToHardware(const QString& fileName)
{
    QFileInfo info(fileName);

    if (!info.exists() || !info.isFile() || !info.isReadable())
    {
        return std::unexpected(ConfigFileShellError::InvalidPath);
    }

    auto* device = context_.device();
    if (!device)
    {
        return std::unexpected(ConfigFileShellError::DeviceContextEmpty);
    }

    sc::FileLoader loader(*device);
    const auto filePath = info.canonicalFilePath().toStdString();
    const auto result = loader.load(filePath);

    if (!result.has_value())
    {
        return std::unexpected(result.error());
    }

    return {};
}

std::expected<void, ConfigError> ConfigFileService::saveFromHardware(const QString& fileName)
{
    QFileInfo info(fileName);
    auto* device = context_.device();
    if (!device)
    {
        return std::unexpected(ConfigFileShellError::DeviceContextEmpty);
    }

    sc::FileSaver saver(*device);
    const auto filePath = info.canonicalFilePath().toStdString();
    const auto result = saver.save(filePath);

    if (!result.has_value())
    {
        return std::unexpected(result.error());
    }

    return {};
}