#include "backend.h"
#include <QDebug>

Backend::Backend(QObject *parent)
    : QObject(parent)
{
}

void Backend::connectDevice()
{
    qInfo() << "Backend::connectDevice() called";
    // TODO: тут будет твой реальный код подключения
}
