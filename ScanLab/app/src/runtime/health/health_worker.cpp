#include "runtime/health/health_worker.h"

#include "runtime/device/device_context.h"

HealthWorker2::HealthWorker2(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
}