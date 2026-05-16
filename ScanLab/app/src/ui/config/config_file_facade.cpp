#include "ui/config/config_file_facade.h"

#include "runtime/config/config_file_worker.h"
#include "runtime/device/device_context.h"

ConfigFileFacade::ConfigFileFacade(DeviceContext& context,
    ShellFacade& shellFacade,
    QObject* parent)
    : shellFacade_{ shellFacade }
    , QObject(parent)
{
    worker_ = new ConfigFileWorker(context, shellFacade.shellServices());
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this,
        &ConfigFileFacade::requestLoad,
        worker_,
        [this]() {
            worker_->loadConfigFile(loadPath_);
        },
        Qt::QueuedConnection);

    connect(this,
        &ConfigFileFacade::requestSave,
        worker_,
        [this]() {
            worker_->saveConfigFile(savePath_);
        },
        Qt::QueuedConnection);

    connect(worker_,
        &ConfigFileWorker::loadCompleted,
        this,
        [this]() {
            setBusy(false);
        },
        Qt::QueuedConnection);


    connect(worker_,
        &ConfigFileWorker::saveCompleted,
        this,
        [this]() {
            setBusy(false);
        },
        Qt::QueuedConnection);

    workerThread_.start();
}

ConfigFileFacade::~ConfigFileFacade()
{
    if (workerThread_.isRunning())
    {
        workerThread_.quit();
        workerThread_.wait();
    }
}

QString ConfigFileFacade::loadPath() const
{
    return loadPath_;
}

QString ConfigFileFacade::savePath() const
{
    return savePath_;
}

bool ConfigFileFacade::busy() const
{
    return busy_;
}

void ConfigFileFacade::setLoadPath(const QString& value)
{
    if (loadPath_ == value)
    {
        return;
    }

    loadPath_ = value;
    emit loadPathChanged();
}

void ConfigFileFacade::setSavePath(const QString& value)
{
    if (savePath_ == value)
    {
        return;
    }

    savePath_ = value;
    emit savePathChanged();
}

void ConfigFileFacade::loadConfigFile()
{
    if (busy_)
    {
        return;
    }

    setBusy(true);
    emit requestLoad();
}

void ConfigFileFacade::saveConfigFile()
{
    if (busy_)
    {
        return;
    }

    setBusy(true);
    emit requestSave();
}

void ConfigFileFacade::setBusy(bool value)
{
    if (busy_ == value)
    {
        return;
    }

    busy_ = value;
    emit busyChanged();
}