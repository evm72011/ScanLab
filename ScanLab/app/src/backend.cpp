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
}

bool Backend::ensureDeviceCreated()
{
    return true;
}

bool Backend::connectDevice()
{
    if (!ensureDeviceCreated()) {
        qWarning() << "[E] device creation failed";
        return false;
    }

    const auto type = device_.type();
    const auto address = device_.address();

    qInfo() << "[connectDevice] type =" << type << ", address =" << address;

    device_.connectDevice();
    return true;
}