#include "runtime/acquisition/ascan/ascan_worker.h"

#include "runtime/device/device_context.h"

namespace saa = scanlab::acquisition::ascan;

AScanWorker::AScanWorker(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
    service_.setFrameHandler([this](saa::Frame&& frame) {
        emit frameUpdated(std::move(frame));
    });
}

void AScanWorker::start()
{
    const auto result = service_.start();
    if (!result.has_value()) {
        emit startFailed();
        return;
    }

    emit started();
}

void AScanWorker::stop()
{
    service_.stop();
    emit stopped(service_.isRunning());
}

void AScanWorker::setCycleFilter(int cycle)
{
    service_.setCycleFilter(cycle);
}

void AScanWorker::setCropMargins(qreal leftFraction, qreal rightFraction)
{
    service_.setCropMargins(
        static_cast<double>(leftFraction),
        static_cast<double>(rightFraction));
}
