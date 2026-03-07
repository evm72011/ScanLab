#pragma once

#include <QObject>
#include <QString>
#include <qqmlintegration.h>
#include <QDebug>

#include "device_type_mapper.h"
#include "scanlab/hardware/device.h"
#include <magic_enum/magic_enum.hpp>

class Device : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(DeviceType::Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(QString lastConnectStatusText READ lastConnectStatusText NOTIFY lastConnectStatusTextChanged)

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
        emit typeChanged();
    }

    QString address() const
    {
        return address_;
    }

    QString lastConnectStatusText() const
    {
        return lastConnectStatusText_;
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

    Q_INVOKABLE int connect()
    {
        hw_.setDevice(toHardware(type_));
        const auto result = hw_.connect(address_.toStdWString());

        lastConnectStatusText_ =
            QString::fromUtf8(magic_enum::enum_name(result).data());

        emit connectedChanged();
        emit lastConnectStatusTextChanged();

        return static_cast<int>(result);
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
    void lastConnectStatusTextChanged();

private:
    DeviceType::Type type_ = DeviceType::OEMPAMax;
    QString address_ { "192.168.1.11" };
    QString lastConnectStatusText_;
    scanlab::hardware::Device hw_;
};
