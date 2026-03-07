#pragma once

#include <QObject>
#include <QString>
#include <qqmlintegration.h>
#include <QDebug>

#include "device_type_mapper.h"
#include "scanlab/hardware/device.h"

class Device : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(DeviceType::Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    explicit Device(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

    DeviceType::Type type() const
    {
        return type_;
    }

    void setType(DeviceType::Type value)
    {
        if (type_ == value)
            return;
        type_ = value;
        hw_.setDevice(toHardware(type_));
        emit typeChanged();
    }

    QString address() const
    {
        return address_;
    }

    void setAddress(const QString &value)
    {
        if (address_ == value)
            return;
        address_ = value;
        emit addressChanged();
    }

    bool connected() const
    {
        return hw_.isConnected();
    }

    Q_INVOKABLE bool connect()
    {
        const auto result = hw_.connect(address_.toStdWString());
        qInfo() << static_cast<int>(result);
        emit connectedChanged();
        return true;
    }

    Q_INVOKABLE void disconnect()
    {
        const bool wasConnected = connected();
        hw_.disconnect();

        if (wasConnected != connected())
            emit connectedChanged();
    }

signals:
    void typeChanged();
    void addressChanged();
    void connectedChanged();

private:
    DeviceType::Type type_ = DeviceType::OEMPAMax;
    QString address_ { "192.168.1.11" };
    scanlab::hardware::Device hw_;
};
