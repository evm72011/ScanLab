#include "runtime/config/config_file_worker.h"
#include "runtime/config/config_file_error.h"

ConfigFileWorker::ConfigFileWorker(DeviceContext& context,
    ShellServices& shellServices,
    QObject* parent)
    : QObject(parent)
    , messageService_(shellServices.messageService())
    , toastService_(shellServices.toastService())
    , service_(context)
{
}

void ConfigFileWorker::loadConfigFile(const QString& fileName)
{
    const auto result = service_.loadToHardware(fileName);
    emit loadCompleted();

    auto title = tr("Device configuration");

    if (result.has_value())
    {
        auto text = tr("Config file successfully loaded");
        toastService_.showInfo(title, text);
        return;
    }

    const auto shortText = tr("Config file load failure");
    const auto& error = result.error();
    const auto errorInfo = describeError(error);
    messageService_.showError(title, shortText, errorInfo);
}


void ConfigFileWorker::saveConfigFile(const QString& fileName)
{
    const auto result = service_.saveFromHardware(fileName);
    emit loadCompleted();

    auto title = tr("Device configuration");

    if (result.has_value())
    {
        auto text = tr("Config file successfully saved");
        toastService_.showInfo(title, text);
        return;
    }

    const auto shortText = tr("Config file save failure");
    const auto& error = result.error();
    const auto errorInfo = describeError(error);
    messageService_.showError(title, shortText, errorInfo);
}