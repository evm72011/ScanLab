#include "runtime/config/config_callback_service.h"

#include "scanlab/config/callback_dispatcher.h"
#include "scanlab/config/config_snapshot.h"

#include <QString>
#include <QVariantList>

namespace sc = scanlab::config;

ConfigCallbackService::ConfigCallbackService() = default;

ConfigCallbackService::~ConfigCallbackService()
{
    stopWatching();
}

void ConfigCallbackService::startWatching(SnapshotHandler handler)
{
    auto& dispatcher = sc::CallbackDispatcher::instance();

    dispatcher.setHandler(
        [handler = std::move(handler)](sc::ConfigSnapshot snapshot) {
            handler(toVariantMap(snapshot));
        });

    dispatcher.registerCallback();
}

void ConfigCallbackService::stopWatching()
{
    auto& dispatcher = sc::CallbackDispatcher::instance();

    dispatcher.clearHandler();
    dispatcher.unregisterCallback();
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
