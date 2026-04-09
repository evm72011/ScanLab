#include "runtime/health/health_worker.h"

#include "runtime/device/device_context.h"

#include <QDebug>

HealthWorker2::HealthWorker2(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
}

void HealthWorker2::poll()
{
    qDebug() << "HealthWorker2::poll";
    const auto snapshot = service_.readTemperature();
    if (!snapshot) {
        emit temperatureUnavailable();
        return;
    }

    emit temperatureUpdated(*snapshot);
}