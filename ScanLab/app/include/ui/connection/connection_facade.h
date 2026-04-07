#pragma once

#include <QObject>
#include <QString>
#include <QThread>

#include "runtime/device/device_type.h"
#include "ui/connection/connection_state2.h"

class DeviceContext;
class ConnectionWorker2;

class ConnectionFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DeviceType2 deviceType READ deviceType WRITE setDeviceType NOTIFY deviceTypeChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(ConnectionState2::State connectionState READ connectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(QString lastConnectStatusCode READ lastConnectStatusCode NOTIFY lastConnectStatusCodeChanged)

public:
    explicit ConnectionFacade(DeviceContext& context, QObject* parent = nullptr);
    ~ConnectionFacade() override;

    DeviceType2 deviceType() const;
    void setDeviceType(DeviceType2 value);

    QString address() const;
    void setAddress(const QString& value);

    ConnectionState2::State connectionState() const;
    QString lastConnectStatusCode() const;

    Q_INVOKABLE void connectDevice();
    Q_INVOKABLE void disconnectDevice();
    Q_INVOKABLE void resetDevice();

signals:
    void deviceTypeChanged();
    void addressChanged();
    void connectionStateChanged();
    void lastConnectStatusCodeChanged();
    void connectFinished(int result); // ← вот это

    void requestConnect(DeviceType2 type, const QString& address);
    void requestDisconnect();
    void requestReset();

private:
    void setConnectionState(ConnectionState2::State value);
    void setLastConnectStatusCode(const QString& value);

private:
    ConnectionWorker2* worker_ = nullptr;
    QThread workerThread_;

    DeviceType2 deviceType_ = DeviceType2::None;
    QString address_;
    ConnectionState2::State connectionState_ = ConnectionState2::State::Disconnected;
    QString lastConnectStatusCode_;
};