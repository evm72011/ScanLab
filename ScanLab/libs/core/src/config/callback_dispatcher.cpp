#include "scanlab/config/callback_dispatcher.h"

//#include <UTKernelDriver.h>
//#include <UTKernelDriverOEMPA.h>

#include <Common.h>
#include <myMFC.h>
#include <UTBasicEnum.h>
#include <UTBasicType.h>
#include <UTDriverCommon.h>
#include <UTDriverTypes.h>
#include <CustomizedKernelOEMPA.h>

namespace scanlab::config {

CallbackDispatcher& CallbackDispatcher::instance()
{
    static CallbackDispatcher dispatcher;
    return dispatcher;
}

void CallbackDispatcher::registerCallback()
{
    OEMPA_SetCallbackCustomizedDriverAPI(&CallbackDispatcher::callback);
}

void CallbackDispatcher::unregisterCallback()
{
    OEMPA_SetCallbackCustomizedDriverAPI(nullptr);
}

void CallbackDispatcher::setHandler(Handler handler)
{
    std::lock_guard lock(mutex_);
    handler_ = std::move(handler);
}

void CallbackDispatcher::clearHandler()
{
    std::lock_guard lock(mutex_);
    handler_ = nullptr;
}

structCorrectionOEMPA* WINAPI CallbackDispatcher::callback(
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

void CallbackDispatcher::handle(
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
            .pointCount = cycle[i].lPointCount
        });
    }

    localHandler(std::move(snapshot));
}

} // namespace scanlab::config