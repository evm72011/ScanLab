#include "device_facade.h"

#include "connection_worker.h"
#include "scanlab/hardware/device.h"

#include <QMetaObject>

DeviceFacade::DeviceFacade(QObject* parent)
    : QObject(parent)
    , hardwareDevice_(std::make_unique<scanlab::hardware::Device>())
{
    connectionWorker_ = new ConnectionWorker(hardwareDevice_.get());
    connectionWorker_->moveToThread(&workerThread_);

    connect(
        &workerThread_,
        &QThread::finished,
        connectionWorker_,
        &QObject::deleteLater);

    connect(
        this,
        &DeviceFacade::requestConnect,
        connectionWorker_,
        &ConnectionWorker::connectDevice,
        Qt::QueuedConnection);

    connect(
        this,
        &DeviceFacade::requestDisconnect,
        connectionWorker_,
        &ConnectionWorker::disconnectDevice,
        Qt::QueuedConnection);

    connect(
        this,
        &DeviceFacade::requestReset,
        connectionWorker_,
        &ConnectionWorker::resetDevice,
        Qt::QueuedConnection);

    connect(
        connectionWorker_,
        &ConnectionWorker::connectCompleted,
        this,
        [this](int result, bool connected, const QString& statusCode) {
            setConnectionState(
                connected
                    ? ConnectionState::Connected
                    : ConnectionState::Disconnected);

            setLastConnectStatusCode(statusCode);
            emit connectFinished(result);
        },
        Qt::QueuedConnection);

    connect(
        connectionWorker_,
        &ConnectionWorker::disconnected,
        this,
        [this](bool stillConnected) {
            if (!stillConnected) {
                setConnectionState(ConnectionState::Disconnected);
            }
        },
        Qt::QueuedConnection);

    connect(
        connectionWorker_,
        &ConnectionWorker::resetCompleted,
        this,
        [this]() {
            setConnectionState(ConnectionState::Disconnected);
        },
        Qt::QueuedConnection);

    workerThread_.start();
}

DeviceFacade::~DeviceFacade()
{
    if (connectionWorker_ != nullptr && workerThread_.isRunning()) {
        QMetaObject::invokeMethod(
            connectionWorker_,
            &ConnectionWorker::resetDevice,
            Qt::BlockingQueuedConnection);
    }

    workerThread_.quit();
    workerThread_.wait();
}

DeviceType::Type DeviceFacade::type() const
{
    return type_;
}

void DeviceFacade::setType(DeviceType::Type value)
{
    if (type_ == value) {
        return;
    }

    type_ = value;
    emit typeChanged();
}

QString DeviceFacade::address() const
{
    return address_;
}

void DeviceFacade::setAddress(const QString& value)
{
    if (address_ == value) {
        return;
    }

    address_ = value;
    emit addressChanged();
}

ConnectionState::State DeviceFacade::connectionState() const
{
    return connectionState_;
}

QString DeviceFacade::lastConnectStatusCode() const
{
    return lastConnectStatusCode_;
}

void DeviceFacade::connectDevice()
{
    if (connectionState_ == ConnectionState::Connecting) {
        return;
    }

    setConnectionState(ConnectionState::Connecting);
    emit requestConnect(type_, address_);
}

void DeviceFacade::disconnectDevice()
{
    if (connectionState_ == ConnectionState::Connecting) {
        return;
    }

    emit requestDisconnect();
}

void DeviceFacade::resetDevice()
{
    emit requestReset();
}

scanlab::hardware::Device* DeviceFacade::hardwareDevice()
{
    return hardwareDevice_.get();
}

const scanlab::hardware::Device* DeviceFacade::hardwareDevice() const
{
    return hardwareDevice_.get();
}

void DeviceFacade::setConnectionState(ConnectionState::State value)
{
    if (connectionState_ == value) {
        return;
    }

    connectionState_ = value;
    emit connectionStateChanged();
}

void DeviceFacade::setLastConnectStatusCode(const QString& value)
{
    if (lastConnectStatusCode_ == value) {
        return;
    }

    lastConnectStatusCode_ = value;
    emit lastConnectStatusCodeChanged();
}