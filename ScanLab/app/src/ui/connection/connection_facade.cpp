#include "ui/connection/connection_facade.h"

#include "runtime/device/device_context.h"
#include "runtime/connection/connection_result.h"
#include "runtime/connection/connection_worker.h"

#include <QMetaObject>
#include <QDebug>

ConnectionFacade::ConnectionFacade(DeviceContext& context, QObject* parent)
    : QObject(parent)
{
    worker_ = new ConnectionWorker2(context);
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
        &ConnectionWorker2::connectDevice,
        Qt::QueuedConnection);

    connect(
        this,
        &ConnectionFacade::requestDisconnect,
        worker_,
        &ConnectionWorker2::disconnectDevice,
        Qt::QueuedConnection);

    connect(
        this,
        &ConnectionFacade::requestReset,
        worker_,
        &ConnectionWorker2::resetDevice,
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConnectionWorker2::connectCompleted,
        this,
        [this](const ConnectionResult& result) {
            setConnectionState(
                result.isConnected
                    ? ConnectionState2::State::Connected
                    : ConnectionState2::State::Disconnected);

            setLastConnectStatusCode(QString::fromStdString(result.statusCode));
            emit connectFinished(result.isConnected ? 0 : 1);  // TODO connectFailure bool ??
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConnectionWorker2::disconnected,
        this,
        [this](bool stillConnected) {
            if (!stillConnected) {
                setConnectionState(ConnectionState2::State::Disconnected);
            }
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &ConnectionWorker2::resetCompleted,
        this,
        [this]() {
            setConnectionState(ConnectionState2::State::Disconnected);
        },
        Qt::QueuedConnection);

    workerThread_.start();
}

ConnectionFacade::~ConnectionFacade()
{
    if (worker_ != nullptr && workerThread_.isRunning()) {
        QMetaObject::invokeMethod(
            worker_,
            &ConnectionWorker2::resetDevice,
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
    qDebug() << "ConnectionFacade::setDeviceType " << (int)value;
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

ConnectionState2::State ConnectionFacade::connectionState() const
{
    return connectionState_;
}

QString ConnectionFacade::lastConnectStatusCode() const
{
    return lastConnectStatusCode_;
}

void ConnectionFacade::connectDevice()
{
    if (connectionState_ == ConnectionState2::State::Connecting) {
        return;
    }

    setConnectionState(ConnectionState2::State::Connecting);
    qDebug() << "ConnectionFacade::connectDevice: " << (int)deviceType_;
    emit requestConnect(deviceType_, address_);
}

void ConnectionFacade::disconnectDevice()
{
    if (connectionState_ == ConnectionState2::State::Connecting) {
        return;
    }

    emit requestDisconnect();
}

void ConnectionFacade::resetDevice()
{
    emit requestReset();
}

void ConnectionFacade::setConnectionState(ConnectionState2::State value)
{
    if (connectionState_ == value) {
        return;
    }

    connectionState_ = value;
    emit connectionStateChanged();
}

void ConnectionFacade::setLastConnectStatusCode(const QString& value)
{
    if (lastConnectStatusCode_ == value) {
        return;
    }

    lastConnectStatusCode_ = value;
    emit lastConnectStatusCodeChanged();
}