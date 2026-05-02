#include "scanlab/config/config_file_callback_dispatcher.h"

#include <CustomizedDriverOEMPA.h>

namespace scanlab::config {

ConfigFileCallbackDispatcher& ConfigFileCallbackDispatcher::instance()
{
    static ConfigFileCallbackDispatcher dispatcher;
    return dispatcher;
}

void ConfigFileCallbackDispatcher::registerCallback()
{
    OEMPA_SetCallbackCustomizedDriverAPI(&ConfigFileCallbackDispatcher::callback);
}

void ConfigFileCallbackDispatcher::unregisterCallback()
{
    OEMPA_SetCallbackCustomizedDriverAPI(nullptr);
}

void ConfigFileCallbackDispatcher::setHandler(Handler handler)
{
    std::lock_guard lock(mutex_);
    handler_ = std::move(handler);
}

void ConfigFileCallbackDispatcher::clearHandler()
{
    std::lock_guard lock(mutex_);
    handler_ = nullptr;
}

structCorrectionOEMPA* WINAPI ConfigFileCallbackDispatcher::callback(
    CHWDeviceOEMPA*,
    const wchar_t* fileName,
    enumStepCustomizedAPI step,
    structRoot* root,
    structCycle* cycle,
    CFocalLaw* emission,
    CFocalLaw* reception)
{
    instance().handle(
        fileName,
        step,
        root,
        cycle,
        emission,
        reception);

    return nullptr;
}

void ConfigFileCallbackDispatcher::handle(
    const wchar_t* fileName,
    enumStepCustomizedAPI step,
    structRoot* root,
    structCycle* cycle,
    CFocalLaw*,
    CFocalLaw*)
{
    if (step != eWriteHW_Leave) {
        return;
    }

    if (!root || !cycle) {
        return;
    }

    Handler localHandler;
    {
        std::lock_guard lock(mutex_);
        localHandler = handler_;
    }

    if (!localHandler) {
        return;
    }

    ConfigSnapshot snapshot;
    snapshot.fileName = fileName ? fileName : L"";
    snapshot.cycleCount = root->iCycleCount;
    snapshot.ascanEnabled = root->bAscanEnable != 0;

    snapshot.cycles.reserve(static_cast<std::size_t>(root->iCycleCount));

    for (int i = 0; i < root->iCycleCount; ++i) {
        snapshot.cycles.push_back(ConfigCycleSnapshot{
            .cycle = i,
            .start = cycle[i].dStart,
            .range = cycle[i].dRange,
            .pointCount = cycle[i].iPointCount
        });
    }

    localHandler(std::move(snapshot));
}

} // namespace scanlab::config