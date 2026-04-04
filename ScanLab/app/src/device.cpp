#include "device.h"
#include "device_worker.h"
#include "scanlab/hardware/device.h"

Device::Device(QObject* parent)
    : QObject(parent), device_(std::make_unique<::scanlab::hardware::Device>())
{
    worker_ = new DeviceWorker();
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(
        this,
        &Device::requestReset,
        worker_,
        &DeviceWorker::resetDevice,
        Qt::QueuedConnection);

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
            setConnectionState(ConnectionState::Connected);
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
            if (stillConnected) {
                // what else ??
                return;
            }
            setConnectionState(ConnectionState::Disconnected);
          },
        Qt::QueuedConnection);

    workerThread_.start();
}

Device::~Device()
{
    if (worker_ && workerThread_.isRunning()) {
        QMetaObject::invokeMethod(
            worker_,
            "resetDevice",
            Qt::BlockingQueuedConnection);
    }

    workerThread_.quit();
    workerThread_.wait();
}

void Device::resetDevice()
{
    emit requestReset();
}

void Device::connectDevice()
{
    if (connectionState_ == ConnectionState::State::Connecting)
        return;

    setConnectionState(ConnectionState::State::Connecting);
    emit requestConnect(type_, address_);
}

void Device::disconnectDevice()
{
    if (connectionState_ == ConnectionState::State::Connecting)
        return;
    emit requestDisconnect();
}

::scanlab::hardware::Device* Device::hardwareDevice()
{
    return device_.get();
}

const ::scanlab::hardware::Device* Device::hardwareDevice() const
{
    return device_.get();
}