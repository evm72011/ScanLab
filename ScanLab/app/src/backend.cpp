#include "backend.h"
#include <QDebug>


Backend::Backend(QObject *parent)
    : QObject(parent)
{
}

bool Backend::ensureDeviceCreated()
{
    return false;
}

bool Backend::connectDevice(const QString& address)
{
    qInfo()    << "Normal info";
    return false;
}
