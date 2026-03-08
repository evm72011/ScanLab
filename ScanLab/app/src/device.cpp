#include "device.h"
#include "device_worker.h"

Device::Device(QObject* parent)
    : QObject(parent)
{
    worker_ = new DeviceWorker();
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(
        this,
        &Device::requestConnect,
        worker_,
        &DeviceWorker::connectDevice,
        Qt::QueuedConnection);

    connect(
        this,
        &Device::requestDisconnect,
        worker_,
        &DeviceWorker::disconnectDevice,
        Qt::QueuedConnection);

    connect(
        worker_,
        &DeviceWorker::connectCompleted,
        this,
        [this](int result, bool isConnected, const QString& statusCode)
        {
            setConnecting(false);
            setConnected(isConnected);
            setLastConnectStatusCode(statusCode);

            emit connectFinished(result);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &DeviceWorker::disconnected,
        this,
        [this](bool stillConnected)
        {
            setConnected(stillConnected);
        },
        Qt::QueuedConnection);

    workerThread_.start();
}

Device::~Device()
{
    workerThread_.quit();
    workerThread_.wait();
}

void Device::connectDevice()
{
    if (connecting_)
        return;

    setConnecting(true);
    emit requestConnect(type_, address_);
}

void Device::disconnectDevice()
{
    if (connecting_)
        return;

    emit requestDisconnect();
}
