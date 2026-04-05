#pragma once

#include <QObject>
#include <QString>
#include <QThread>
#include <qqmlintegration.h>

#include <memory>

#include "connection_state.h"
#include "device_type.h"
#include "connection_worker.h"

class DeviceWorker;

namespace scanlab::hardware {
class Device;
}

class DeviceFacade : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(DeviceType::Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(ConnectionState::State connectionState READ connectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(QString lastConnectStatusCode READ lastConnectStatusCode NOTIFY lastConnectStatusCodeChanged)

public:
    explicit DeviceFacade(QObject* parent = nullptr);
    ~DeviceFacade() override;

    DeviceType::Type type() const;
    void setType(DeviceType::Type value);

    QString address() const;
    void setAddress(const QString& value);

    ConnectionState::State connectionState() const;
    QString lastConnectStatusCode() const;

    Q_INVOKABLE void connectDevice();
    Q_INVOKABLE void disconnectDevice();
    Q_INVOKABLE void resetDevice();

    scanlab::hardware::Device* hardwareDevice();
    const scanlab::hardware::Device* hardwareDevice() const;

signals:
    void typeChanged();
    void addressChanged();
    void connectionStateChanged();
    void lastConnectStatusCodeChanged();

    void requestConnect(DeviceType::Type type, QString address);
    void requestDisconnect();
    void requestReset();

    void connectFinished(int result);

private:
    void setConnectionState(ConnectionState::State value);
    void setLastConnectStatusCode(const QString& value);

private:
    DeviceType::Type type_ = DeviceType::OEMPA_Max;
    QString address_ = QStringLiteral("192.168.1.11");

    ConnectionState::State connectionState_ = ConnectionState::Disconnected;
    QString lastConnectStatusCode_;

    std::unique_ptr<scanlab::hardware::Device> hardwareDevice_;

    QThread workerThread_;
    ConnectionWorker* connectionWorker_ = nullptr;
};