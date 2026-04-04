#include "device_controller.h"

#include "connection_worker.h"
#include "scanlab/hardware/device.h"

#include <QMetaObject>

DeviceController::DeviceController(QObject* parent)
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
        &DeviceController::requestConnect,
        connectionWorker_,
        &ConnectionWorker::connectDevice,
        Qt::QueuedConnection);

    connect(
        this,
        &DeviceController::requestDisconnect,
        connectionWorker_,
        &ConnectionWorker::disconnectDevice,
        Qt::QueuedConnection);

    connect(
        this,
        &DeviceController::requestReset,
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

DeviceController::~DeviceController()
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

DeviceType::Type DeviceController::type() const
{
    return type_;
}

void DeviceController::setType(DeviceType::Type value)
{
    if (type_ == value) {
        return;
    }

    type_ = value;
    emit typeChanged();
}

QString DeviceController::address() const
{
    return address_;
}

void DeviceController::setAddress(const QString& value)
{
    if (address_ == value) {
        return;
    }

    address_ = value;
    emit addressChanged();
}

ConnectionState::State DeviceController::connectionState() const
{
    return connectionState_;
}

QString DeviceController::lastConnectStatusCode() const
{
    return lastConnectStatusCode_;
}

void DeviceController::connectDevice()
{
    if (connectionState_ == ConnectionState::Connecting) {
        return;
    }

    setConnectionState(ConnectionState::Connecting);
    emit requestConnect(type_, address_);
}

void DeviceController::disconnectDevice()
{
    if (connectionState_ == ConnectionState::Connecting) {
        return;
    }

    emit requestDisconnect();
}

void DeviceController::resetDevice()
{
    emit requestReset();
}

scanlab::hardware::Device* DeviceController::hardwareDevice()
{
    return hardwareDevice_.get();
}

const scanlab::hardware::Device* DeviceController::hardwareDevice() const
{
    return hardwareDevice_.get();
}

void DeviceController::setConnectionState(ConnectionState::State value)
{
    if (connectionState_ == value) {
        return;
    }

    connectionState_ = value;
    emit connectionStateChanged();
}

void DeviceController::setLastConnectStatusCode(const QString& value)
{
    if (lastConnectStatusCode_ == value) {
        return;
    }

    lastConnectStatusCode_ = value;
    emit lastConnectStatusCodeChanged();
}