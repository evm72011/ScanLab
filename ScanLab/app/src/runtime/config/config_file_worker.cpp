#include "runtime/config/config_file_worker.h"

#include <magic_enum/magic_enum.hpp>

ConfigFileWorker::ConfigFileWorker(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
}

void ConfigFileWorker::refreshConfigFiles()
{
    const auto files = service_.availableConfigFiles();

    if (!files.has_value()) {
        const auto errorCode = QString::fromUtf8(
            magic_enum::enum_name(files.error()).data());

        emit configFilesErrorCode(errorCode);
        return;
    }

    emit configFilesUpdated(*files);
}

void ConfigFileWorker::loadConfigFile(QString fileName)
{
    const auto result = service_.loadToHardware(fileName);

    if (!result.has_value()) {
        const auto errorCode = QString::fromUtf8(
            magic_enum::enum_name(result.error()).data());

        emit configFileLoadFailed(fileName, errorCode);
        return;
    }

    emit configFileLoaded(fileName);
}
