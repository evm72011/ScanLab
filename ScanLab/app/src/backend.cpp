#include <Windows.h>

#include <UTDriverOEMPA.h>
#include <UTDriverOEMPAExport.h>
#include <UTDriverOEMPAmax.h>

#include "backend.h"

#include <QDebug>

Backend::Backend(QObject* parent)
    : QObject(parent)
{
    device_.setType(DeviceType::OEMPA_Max);
    healthMonitor_.setDevice(&device_);

    connect(&device_,
            &DeviceFacade::connectionStateChanged,
            this,
            [this]() {
                setConnected(
                    device_.connectionState() == ConnectionState::Connected);
            });
}

void Backend::setConnected(bool value)
{
    if (connected_ == value) {
        return;
    }

    connected_ = value;
    emit connectedChanged();
}

bool Backend::ensureDeviceCreated()
{
    return true;
}

bool Backend::connectDevice()
{
    if (!ensureDeviceCreated()) {
        qWarning() << "[E] device creation failed";
        setConnected(false);
        return false;
    }

    const auto type = device_.type();
    const auto address = device_.address();

    qInfo() << "[connectDevice] type =" << type << ", address =" << address;

    device_.connectDevice();
    return true;
}