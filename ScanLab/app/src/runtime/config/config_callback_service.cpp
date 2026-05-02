#include "runtime/device/device_context.h"
#include "runtime/config/config_callback_service.h"

#include "scanlab/config/callback_dispatcher.h"
#include "scanlab/config/config_snapshot.h"

#include <QString>
#include <QVariantList>

namespace sc = scanlab::config;

ConfigCallbackService::ConfigCallbackService(DeviceContext& context)
    : dispatcher_(std::make_unique<sc::CallbackDispatcher>(*context.device()))
{
}

ConfigCallbackService::~ConfigCallbackService()
{
    stopWatching();
}

void ConfigCallbackService::startWatching(SnapshotHandler handler)
{
    if (!dispatcher_) {
        return;
    }

    dispatcher_->setHandler(
        [handler = std::move(handler)](sc::ConfigSnapshot snapshot) {
            handler(toVariantMap(snapshot));
        });

    dispatcher_->registerCallback();
}

void ConfigCallbackService::stopWatching()
{
    if (!dispatcher_) {
        return;
    }

    dispatcher_->clearHandler();
    dispatcher_->unregisterCallback();
}

QVariantMap ConfigCallbackService::toVariantMap(
    const sc::ConfigSnapshot& snapshot)
{
    QVariantList cycles;

    for (const auto& c : snapshot.cycles) {
        QVariantMap item;
        item["cycle"] = c.cycle;
        item["start"] = c.start;
        item["range"] = c.range;
        item["pointCount"] = c.pointCount;
        cycles.push_back(item);
    }

    QVariantMap result;
    result["fileName"] = QString::fromStdWString(snapshot.fileName);
    result["cycleCount"] = snapshot.cycleCount;
    result["ascanEnabled"] = snapshot.ascanEnabled;
    result["cycles"] = cycles;

    return result;
}
