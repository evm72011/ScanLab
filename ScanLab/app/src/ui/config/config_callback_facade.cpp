#include "ui/config/config_callback_facade.h"

#include "runtime/config/config_callback_worker.h"
#include "runtime/device/device_context.h"

ConfigCallbackFacade::ConfigCallbackFacade(DeviceContext& context, QObject* parent)
    : QObject(parent)
{
    worker_ = new ConfigCallbackWorker(context);
    worker_->moveToThread(&workerThread_);

    connect(
        &workerThread_,
        &QThread::finished,
        worker_,
        &QObject::deleteLater);

    connect(
        this,
        &ConfigCallbackFacade::requestStartWatching,
        worker_,
        &ConfigCallbackWorker::startWatching,
        Qt::QueuedConnection);

    connect(
        this,
        &ConfigCallbackFacade::requestStopWatching,
        worker_,
        &ConfigCallbackWorker::stopWatching,
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConfigCallbackWorker::configSnapshotUpdated,
        this,
        [this](const QVariantMap& snapshot) {
            setConfigSnapshot(snapshot);
        },
        Qt::QueuedConnection);

    workerThread_.start();
}

ConfigCallbackFacade::~ConfigCallbackFacade()
{
    emit requestStopWatching();

    if (workerThread_.isRunning()) {
        workerThread_.quit();
        workerThread_.wait();
    }
}

QVariantMap ConfigCallbackFacade::configSnapshot() const
{
    return configSnapshot_;
}

void ConfigCallbackFacade::startWatching()
{
    emit requestStartWatching();
}

void ConfigCallbackFacade::stopWatching()
{
    emit requestStopWatching();
}

void ConfigCallbackFacade::setConfigSnapshot(const QVariantMap& value)
{
    configSnapshot_ = value;
    emit configSnapshotChanged();
}
