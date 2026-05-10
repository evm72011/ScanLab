#pragma once

#include <QObject>
#include <QString>
#include <QThread>

#include "runtime/device/device_type.h"
#include "runtime/errors/error_info.h"
#include "ui/connection/connection_state.h"
#include "ui/shell/shell_facade.h"

class DeviceContext;
class ConnectionWorker;

class ConnectionFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DeviceType deviceType READ deviceType WRITE setDeviceType NOTIFY deviceTypeChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(
        ConnectionState::State connectionState READ connectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(QString errorCode READ errorCode NOTIFY errorCodeChanged)
    Q_PROPERTY(QString errorText READ errorText NOTIFY errorTextChanged)
    Q_PROPERTY(QString serialNumber READ serialNumber NOTIFY serialNumberChanged)

public:
    explicit ConnectionFacade(DeviceContext& context,
        ShellFacade& shellFacade,
        QObject* parent = nullptr);
    ~ConnectionFacade() override;

    DeviceType deviceType() const;
    void setDeviceType(DeviceType value);

    QString address() const;
    void setAddress(const QString& value);

    ConnectionState::State connectionState() const;
    QString errorCode() const;
    QString errorText() const;
    QString serialNumber() const;

    Q_INVOKABLE void connectDevice();
    Q_INVOKABLE void disconnectDevice();

signals:
    void deviceTypeChanged();
    void addressChanged();
    void connectionStateChanged();
    void errorCodeChanged();
    void errorTextChanged();
    void serialNumberChanged();
    void connectionFailure();

    void requestConnect(DeviceType type, const QString& address);
    void requestDisconnect();
    void requestReset();

private:
    void setConnectionState(ConnectionState::State value);
    void setErrorInfo(const ErrorInfo& value);
    void setSerialNumber(const QString& value);

private:
    ShellFacade& shellFacade_;
    ConnectionWorker* worker_ = nullptr;
    QThread workerThread_;

    DeviceType deviceType_ = DeviceType::None;
    QString address_;
    ConnectionState::State connectionState_ = ConnectionState::State::Disconnected;
    ErrorInfo errorInfo_;
    QString serialNumber_;
};