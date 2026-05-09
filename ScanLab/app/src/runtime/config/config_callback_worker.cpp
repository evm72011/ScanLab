#include "runtime/config/config_callback_worker.h"

ConfigCallbackWorker::ConfigCallbackWorker(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
}

ConfigCallbackWorker::~ConfigCallbackWorker()
{
    service_.stopWatching();
}

void ConfigCallbackWorker::startWatching()
{
    service_.startWatching([this](QVariantMap snapshot) { emit configSnapshotUpdated(snapshot); });
}

void ConfigCallbackWorker::stopWatching()
{
    service_.stopWatching();
}
