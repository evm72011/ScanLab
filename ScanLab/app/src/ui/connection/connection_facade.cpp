#include "ui/connection/connection_facade.h"

#include "runtime/device/device_context.h"
#include "runtime/connection/connection_worker.h"

#include <QMetaObject>

ConnectionFacade::ConnectionFacade(DeviceContext& context, QObject* parent)
    : QObject(parent)
{
    worker_ = new ConnectionWorker(context);
    worker_->moveToThread(&workerThread_);

    connect(
        &workerThread_,
        &QThread::finished,
        worker_,
        &QObject::deleteLater);

    connect(
        this,
        &ConnectionFacade::requestConnect,
        worker_,
        &ConnectionWorker::connect,
        Qt::QueuedConnection);

    connect(
        this,
        &ConnectionFacade::requestDisconnect,
        worker_,
        &ConnectionWorker::disconnect,
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConnectionWorker::connectionSucces,
        this,
        [this]() {
            setConnectionState(ConnectionState::State::Connected);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConnectionWorker::connectionFailure,
        this,
        [this]() {
            setConnectionState(ConnectionState::State::Disconnected);      // bug if already connected error
            emit connectionFailure();
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConnectionWorker::connectionErrorCode,
        this,
        [this](const QString& code) {
            setConnectionErrorCode(code);      // bug if already connected error
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConnectionWorker::disconnectCompleted,
        this,
        [this](bool stillConnected) {
            if (!stillConnected) {
                setConnectionState(ConnectionState::State::Disconnected);
            }
        },
        Qt::QueuedConnection);

    workerThread_.start();
}

ConnectionFacade::~ConnectionFacade()
{
    if (worker_ != nullptr && workerThread_.isRunning()) {
        QMetaObject::invokeMethod(
            worker_,
            &ConnectionWorker::disconnect,
            Qt::BlockingQueuedConnection);
    }

    workerThread_.quit();
    workerThread_.wait();
}

DeviceType2 ConnectionFacade::deviceType() const
{
    return deviceType_;
}

void ConnectionFacade::setDeviceType(DeviceType2 value)
{
    if (deviceType_ == value) {
        return;
    }

    deviceType_ = value;
    emit deviceTypeChanged();
}

QString ConnectionFacade::address() const
{
    return address_;
}

void ConnectionFacade::setAddress(const QString& value)
{
    if (address_ == value) {
        return;
    }

    address_ = value;
    emit addressChanged();
}

ConnectionState::State ConnectionFacade::connectionState() const
{
    return connectionState_;
}

QString ConnectionFacade::connectionErrorCode() const
{
    return connectionErrorCode_;
}

void ConnectionFacade::connectDevice()
{
    if (connectionState_ != ConnectionState::State::Disconnected) {
        return;
    }

    setConnectionState(ConnectionState::State::Connecting);
    emit requestConnect(deviceType_, address_);
}

void ConnectionFacade::disconnectDevice()
{
    if (connectionState_ != ConnectionState::State::Connected) {
        return;
    }

    setConnectionState(ConnectionState::State::Disconnecting);
    emit requestDisconnect();
}

void ConnectionFacade::setConnectionState(ConnectionState::State value)
{
    if (connectionState_ == value) {
        return;
    }

    connectionState_ = value;
    emit connectionStateChanged();
}

void ConnectionFacade::setConnectionErrorCode(const QString& value)
{
    if (connectionErrorCode_ == value) {
        return;
    }

    connectionErrorCode_ = value;
    emit connectionErrorCodeChanged();
}