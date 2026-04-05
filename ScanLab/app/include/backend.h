#pragma once

#include <QObject>
#include <QString>

#include "device_facade.h"

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(DeviceFacade* device READ device CONSTANT)

public:
    explicit Backend(QObject *parent = nullptr);

    Q_INVOKABLE bool connectDevice();
    bool connected() const { return connected_; }

    DeviceFacade* device() { return &device_; }

signals:
    void connectedChanged();

private:
    bool ensureDeviceCreated();
    void setConnected(bool value);

private:
    bool connected_ = false;
    DeviceFacade device_{this};
};
