#include "ui/connection/connection_facade.h"

#include "runtime/device/device_context.h"
#include "runtime/connection/connection_worker.h"

#include <QMetaObject>
#include <QDebug>
#include <QCoreApplication>

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
        [this](const ConnectionResult& value) {
            setSerialNumber(value.serialNumber);
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
        &ConnectionWorker::errorInfo,
        this,
        [this](const ErrorInfo& errorInfo) {
            setErrorInfo(errorInfo);      // bug if already connected error
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

DeviceType ConnectionFacade::deviceType() const
{
    return deviceType_;
}

void ConnectionFacade::setDeviceType(DeviceType value)
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

QString ConnectionFacade::errorCode() const
{
    return errorInfo_.technicalCode;
}

QString ConnectionFacade::errorText() const
{
    return errorInfo_.message();
}

QString ConnectionFacade::serialNumber() const
{
    return serialNumber_;
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

void ConnectionFacade::setErrorInfo(const ErrorInfo& value)
{
    //if (connectionErrorCode_ == value) { TODO
    //    return;
    //}
    auto old = errorInfo_;
    errorInfo_ = value;

    if (old.technicalCode != value.technicalCode) {
        emit errorCodeChanged();
    }

    if (old.textKey != value.textKey) {
        emit errorTextChanged();
    }
}

void ConnectionFacade::setSerialNumber(const QString& value)
{
    if (serialNumber_ == value) {
        return;
    }

    serialNumber_ = value;
    emit serialNumberChanged();
}