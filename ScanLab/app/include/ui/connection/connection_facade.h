#pragma once

#include <QObject>
#include <QString>
#include <QThread>

#include "runtime/device/device_type.h"
#include "ui/connection/connection_state.h"

class DeviceContext;
class ConnectionWorker2;

class ConnectionFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DeviceType2 deviceType READ deviceType WRITE setDeviceType NOTIFY deviceTypeChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(ConnectionState::State connectionState READ connectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(QString connectionErrorCode READ connectionErrorCode NOTIFY connectionErrorCodeChanged)

public:
    explicit ConnectionFacade(DeviceContext& context, QObject* parent = nullptr);
    ~ConnectionFacade() override;

    DeviceType2 deviceType() const;
    void setDeviceType(DeviceType2 value);

    QString address() const;
    void setAddress(const QString& value);

    ConnectionState::State connectionState() const;
    QString connectionErrorCode() const;

    Q_INVOKABLE void connectDevice();
    Q_INVOKABLE void disconnectDevice();

signals:
    void deviceTypeChanged();
    void addressChanged();
    void connectionStateChanged();
    void connectionErrorCodeChanged();
    void connectionFailure();

    void requestConnect(DeviceType2 type, const QString& address);
    void requestDisconnect();
    void requestReset();

private:
    void setConnectionState(ConnectionState::State value);
    void setConnectionErrorCode(const QString& value);

private:
    ConnectionWorker2* worker_ = nullptr;
    QThread workerThread_;

    DeviceType2 deviceType_ = DeviceType2::None;
    QString address_;
    ConnectionState::State connectionState_ = ConnectionState::State::Disconnected;
    QString connectionErrorCode_;
};