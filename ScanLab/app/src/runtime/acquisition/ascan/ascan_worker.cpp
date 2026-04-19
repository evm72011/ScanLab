#include "runtime/acquisition/ascan/ascan_worker.h"

#include "runtime/device/device_context.h"

AScanWorker::AScanWorker(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
    service_.setFrameHandler([this](scanlab::acquisition::AScanFrame&& frame) {
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
