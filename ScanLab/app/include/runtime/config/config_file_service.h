#pragma once

#include <QString>
#include <QStringList>
#include <expected>

#include "runtime/config/config_file_error.h"

class DeviceContext;

class ConfigFileService
{
public:
    using SnapshotHandler = std::function<void(QVariantMap)>;

    explicit ConfigFileService(DeviceContext& context);

    std::expected<void, ConfigFileError> loadToHardware(const QString& fileName);
    std::expected<void, ConfigFileError> saveFromHardware(const QString& fileName);

private:
    DeviceContext& context_;
};
