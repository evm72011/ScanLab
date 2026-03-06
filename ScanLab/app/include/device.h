#pragma once

#include <QObject>
#include <QString>
#include <qqmlintegration.h>

#include "devicetype.h"

class Device : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(DeviceType::Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)

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

    void setAddress(const QString &value)
    {
        if (address_ == value)
            return;
        address_ = value;
        emit addressChanged();
    }

signals:
    void typeChanged();
    void addressChanged();

private:
    DeviceType::Type type_ = DeviceType::OEMPAMax;
    QString address_;
};
