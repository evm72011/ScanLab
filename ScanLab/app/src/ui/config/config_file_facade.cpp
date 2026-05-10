#include "ui/config/config_file_facade.h"

#include "runtime/config/config_file_worker.h"
#include "runtime/device/device_context.h"

ConfigFileFacade::ConfigFileFacade(DeviceContext& context, ShellFacade& shellFacade, QObject* parent)
    : shellFacade_{ shellFacade }
    , QObject(parent)
{
    worker_ = new ConfigFileWorker(context, shellFacade.shellServices());
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this,
        &ConfigFileFacade::requestRefreshConfigFiles,
        worker_,
        &ConfigFileWorker::refreshConfigFiles,
        Qt::QueuedConnection);

    connect(this,
        &ConfigFileFacade::requestLoadConfigFile,
        worker_,
        &ConfigFileWorker::loadConfigFile,
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConfigFileWorker::configFilesUpdated,
        this,
        [this](const QStringList& files) {
            setAvailableConfigFiles(files);
            setErrorCode({});
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConfigFileWorker::configFilesErrorCode,
        this,
        [this](const QString& value) { setErrorCode(value); },
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConfigFileWorker::configFileLoaded,
        this,
        [this](const QString& fileName) {
            setLoading(false);
            setErrorCode({});
            emit configFileLoaded(fileName);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConfigFileWorker::configFileLoadFailed,
        this,
        [this](const QString& fileName, const QString& errorCode) {
            setLoading(false);
            setErrorCode(errorCode);
            emit configFileLoadFailed(fileName, errorCode);
        },
        Qt::QueuedConnection);

    workerThread_.start();

    refreshConfigFiles();
}

ConfigFileFacade::~ConfigFileFacade()
{
    if (workerThread_.isRunning())
    {
        workerThread_.quit();
        workerThread_.wait();
    }
}

QStringList ConfigFileFacade::availableConfigFiles() const
{
    return availableConfigFiles_;
}

QString ConfigFileFacade::selectedConfigFile() const
{
    return selectedConfigFile_;
}

void ConfigFileFacade::setSelectedConfigFile(const QString& value)
{
    if (selectedConfigFile_ == value)
    {
        return;
    }

    selectedConfigFile_ = value;
    emit selectedConfigFileChanged();
}

bool ConfigFileFacade::loading() const
{
    return loading_;
}

QString ConfigFileFacade::errorCode() const
{
    return errorCode_;
}

void ConfigFileFacade::refreshConfigFiles()
{
    emit requestRefreshConfigFiles();
}

void ConfigFileFacade::loadSelectedConfigFile()
{
    if (loading_)
    {
        return;
    }

    setLoading(true);
    setErrorCode({});

    emit requestLoadConfigFile(selectedConfigFile_);
}

void ConfigFileFacade::setAvailableConfigFiles(const QStringList& value)
{
    if (availableConfigFiles_ == value)
    {
        return;
    }

    availableConfigFiles_ = value;
    emit availableConfigFilesChanged();
}

void ConfigFileFacade::setLoading(bool value)
{
    if (loading_ == value)
    {
        return;
    }

    loading_ = value;
    emit loadingChanged();
}

void ConfigFileFacade::setErrorCode(const QString& value)
{
    if (errorCode_ == value)
    {
        return;
    }

    errorCode_ = value;
    emit errorCodeChanged();
}
