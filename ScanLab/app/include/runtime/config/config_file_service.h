#pragma once

#include <QString>
#include <QStringList>
#include <expected>

class DeviceContext;

enum class ConfigFileError
{
    ConfigDirNotFound,
    InvalidPath,
    HardwareNotSet,
    LoadFailed
};

class ConfigFileService
{
public:
    using SnapshotHandler = std::function<void(QVariantMap)>;

    explicit ConfigFileService(DeviceContext& context);

    std::expected<QStringList, ConfigFileError> availableConfigFiles() const;
    std::expected<void, ConfigFileError> loadToHardware(const QString& fileName);

private:
    std::expected<QString, ConfigFileError> resolveConfigPath(const QString& fileName) const;

    DeviceContext& context_;
    QString configDir_;
};
