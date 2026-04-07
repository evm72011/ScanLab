#include "ui/health/health_facade.h"

#include "runtime/device/device_context.h"
#include "runtime/health/health_worker.h"

HealthFacade::HealthFacade(DeviceContext& context, QObject* parent)
    : QObject(parent)
{
    worker_ = new HealthWorker2(context);
    worker_->moveToThread(&workerThread_);
    // connectors
    workerThread_.start();
}

HealthFacade::~HealthFacade()
{
    if (worker_ != nullptr && workerThread_.isRunning()) {
    // Stop health acquisition
    //    QMetaObject::invokeMethod(
    //        worker_,
    //        &ConnectionWorker2::resetDevice,
    //        Qt::BlockingQueuedConnection);
    }
    workerThread_.quit();
    workerThread_.wait();
}
