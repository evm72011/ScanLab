#pragma once

#include <QObject>
#include <QString>

#include "device.h"

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(Device* device READ device CONSTANT)

public:
    explicit Backend(QObject *parent = nullptr);

    Q_INVOKABLE bool connectDevice();
    bool connected() const { return connected_; }

    Device* device() { return &device_; }

signals:
    void connectedChanged();

private:
    bool ensureDeviceCreated();
    void setConnected(bool value);

private:
    bool connected_ = false;
    Device device_{this};

    // TODO: реальный указатель на девайс
    // std::unique_ptr<CHWDeviceOEMPAmax> hw_;
};
