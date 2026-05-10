#include "runtime/config/config_file_worker.h"

#include <magic_enum/magic_enum.hpp>

ConfigFileWorker::ConfigFileWorker(DeviceContext& context,
    ShellServices& shellServices,
    QObject* parent)
    : QObject(parent)
    , toastService_(shellServices.toastService())
    , service_(context)
{
}

void ConfigFileWorker::refreshConfigFiles()
{
    const auto files = service_.availableConfigFiles();

    if (!files.has_value())
    {
        const auto errorCode = QString::fromUtf8(magic_enum::enum_name(files.error()).data());

        emit configFilesErrorCode(errorCode);
        return;
    }

    emit configFilesUpdated(*files);
}

void ConfigFileWorker::loadConfigFile(const QString& fileName)
{
    const auto result = service_.loadToHardware(fileName);

    if (result.has_value())
    {
        emit configFileLoaded(fileName);

        auto title = tr("Device").toStdString();
        auto text = tr("Config file successfully loaded").toStdString();
        toastService_.showInfo(title, text);
        return;
    }

    // TODO dialog
    const auto errorCode = QString::fromUtf8(magic_enum::enum_name(result.error()).data());

    auto title = tr("Device").toStdString();
    const auto text =
        tr("Config file load failure (%1)")
            .arg(errorCode)
            .toStdString();
    toastService_.showError(title, text);
    emit configFileLoadFailed(fileName, errorCode);
}
