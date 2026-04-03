#pragma once

#include <QObject>
#include <QString>
#include <QThread>
#include <qqmlintegration.h>

#include <memory>

#include "device_type.h"

class DeviceWorker;

namespace scanlab::hardware {
class Device;
}

class Device : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(DeviceType::Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(bool connecting READ connecting NOTIFY connectingChanged)
    Q_PROPERTY(QString lastConnectStatusCode READ lastConnectStatusCode NOTIFY lastConnectStatusCodeChanged)

public:
    explicit Device(QObject* parent = nullptr);
    ~Device();

    DeviceType::Type type() const
    {
        return type_;
    }

    void setType(DeviceType::Type value)
    {
        if (type_ == value)
            return;

        type_ = value;
        emit typeChanged();
    }

    QString address() const
    {
        return address_;
    }

    void setAddress(const QString& value)
    {
        if (address_ == value)
            return;

        address_ = value;
        emit addressChanged();
    }

    bool connected() const
    {
        return connected_;
    }

    bool connecting() const
    {
        return connecting_;
    }

    QString lastConnectStatusCode() const
    {
        return lastConnectStatusCode_;
    }

    Q_INVOKABLE void connectDevice();
    Q_INVOKABLE void disconnectDevice();
    Q_INVOKABLE void resetDevice();

    ::scanlab::hardware::Device* hardwareDevice();
    const ::scanlab::hardware::Device* hardwareDevice() const;

signals:
    void typeChanged();
    void addressChanged();
    void connectedChanged();
    void connectingChanged();
    void lastConnectStatusCodeChanged();

    void requestConnect(DeviceType::Type type, QString address);
    void requestDisconnect();
    void requestReset();

    void connectFinished(int result);

private:
    void setConnected(bool value)
    {
        if (connected_ == value)
            return;

        connected_ = value;
        emit connectedChanged();
    }

    void setConnecting(bool value)
    {
        if (connecting_ == value)
            return;

        connecting_ = value;
        emit connectingChanged();
    }

    void setLastConnectStatusCode(const QString& value)
    {
        if (lastConnectStatusCode_ == value)
            return;

        lastConnectStatusCode_ = value;
        emit lastConnectStatusCodeChanged();
    }

private:
    DeviceType::Type type_ = DeviceType::OEMPA_Max;
    QString address_{"192.168.1.11"};

    bool connected_ = false;
    bool connecting_ = false;
    QString lastConnectStatusCode_;

    QThread workerThread_;
    DeviceWorker* worker_ = nullptr;

    std::unique_ptr<::scanlab::hardware::Device> device_;
};