#include "runtime/config/config_file_service.h"
#include "runtime/device/device_context.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

#include "scanlab/config/file_loader.h"

namespace sc = scanlab::config;

ConfigFileService::ConfigFileService(DeviceContext& context)
    : context_(context)
    , configDir_(QCoreApplication::applicationDirPath() + "/OEMPA_config")
{
}

std::expected<QStringList, ConfigFileError>
ConfigFileService::availableConfigFiles() const
{
    QDir dir(configDir_);

    if (!dir.exists()) {
        return std::unexpected(ConfigFileError::ConfigDirNotFound);
    }

    const QStringList filters {
        "*.txt",
        "*.bin"
    };

    return dir.entryList(
        filters,
        QDir::Files | QDir::Readable,
        QDir::Name
        );
}

std::expected<void, ConfigFileError>
ConfigFileService::loadToHardware(const QString& fileName)
{
    const auto path = resolveConfigPath(fileName);
    if (!path.has_value()) {
        return std::unexpected(path.error());
    }

    auto* device = context_.device();
    if (!device) {
        return std::unexpected(ConfigFileError::HardwareNotSet);
    }

    sc::FileLoader loader(*device);

    const auto result = loader.load(path->toStdString());

    if (!result.has_value()) {
        return std::unexpected(ConfigFileError::LoadFailed);
    }

    return {};
}

std::expected<QString, ConfigFileError>
ConfigFileService::resolveConfigPath(const QString& fileName) const
{
    const QDir dir(configDir_);

    if (!dir.exists()) {
        return std::unexpected(ConfigFileError::ConfigDirNotFound);
    }

    const QString fullPath = dir.absoluteFilePath(fileName);
    const QFileInfo info(fullPath);

    const QString canonical = QDir::cleanPath(info.canonicalFilePath());
    const QString base = QDir::cleanPath(dir.canonicalPath());

    if (canonical.isEmpty()) {
        return std::unexpected(ConfigFileError::InvalidPath);
    }

    if (canonical != base && !canonical.startsWith(base + "/")) {
        return std::unexpected(ConfigFileError::InvalidPath);
    }

    return canonical;
}
