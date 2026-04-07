#include "ui/health/health_facade.h"

#include "runtime/device/device_context.h"

HealthFacade::HealthFacade(DeviceContext& context, QObject* parent)
    : QObject(parent)
{
    //worker_ = new ConnectionWorker2(context);
    //worker_->moveToThread(&workerThread_);
    // connectors
    workerThread_.start();
}

HealthFacade::~HealthFacade()
{
    workerThread_.quit();
    workerThread_.wait();
}
