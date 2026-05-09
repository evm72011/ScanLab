#include "scanlab/config/callback_dispatcher.h"

#include <myMFC.h>
#include "CustomizedKernelOEMPA.h"


#include <mutex>

namespace scanlab::config
{
namespace
{

std::mutex g_activeDispatcherMutex;
CallbackDispatcher* g_activeDispatcher = nullptr;

} // namespace

CallbackDispatcher::CallbackDispatcher(scanlab::device::Device& device)
    : device_(device)
{
}

CallbackDispatcher::~CallbackDispatcher()
{
    unregisterCallback();
}

void CallbackDispatcher::registerCallback()
{
    auto* hw = device_.get();
    if (!hw)
    {
        return;
    }

    {
        std::lock_guard lock(g_activeDispatcherMutex);
        g_activeDispatcher = this;
    }

    //hw->SetAcquisitionParameter(this);
    auto ok = OEMPA_SetCallbackCustomizedDriverAPI(&CallbackDispatcher::callback);
    if (ok)
        printf("OEMPA_SetCallbackCustomizedDriverAPI: SUCCESS\n");
    else
        printf("OEMPA_SetCallbackCustomizedDriverAPI: FAILURE\n");
    fflush(stdout);

    std::lock_guard lock(mutex_);
    registered_ = true;
}

void CallbackDispatcher::unregisterCallback()
{
    bool wasRegistered = false;

    auto* hw = device_.get();
    if (hw)
    {
        hw->SetAcquisitionParameter(nullptr);
    }

    {
        std::lock_guard lock(mutex_);
        wasRegistered = registered_;
        registered_ = false;
    }

    if (!wasRegistered)
    {
        return;
    }

    OEMPA_SetCallbackCustomizedDriverAPI(nullptr);

    {
        std::lock_guard lock(g_activeDispatcherMutex);
        if (g_activeDispatcher == this)
        {
            g_activeDispatcher = nullptr;
        }
    }
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

structCorrectionOEMPA* WINAPI CallbackDispatcher::callback(CHWDeviceOEMPA* hw,
    const wchar_t* fileName,
    enumStepCustomizedAPI step,
    structRoot* root,
    structCycle* cycle,
    CFocalLaw* emission,
    CFocalLaw* reception)
{

    printf("CALLBACK FIRED\n");
    fflush(stdout);

    CallbackDispatcher* dispatcher = nullptr;

    {
        std::lock_guard lock(g_activeDispatcherMutex);
        dispatcher = g_activeDispatcher;
    }

    if (dispatcher)
    {
        dispatcher->handle(hw, fileName, step, root, cycle, emission, reception);
    }

    return nullptr;
}

void CallbackDispatcher::handle(CHWDeviceOEMPA* hw,
    const wchar_t* fileName,
    enumStepCustomizedAPI step,
    structRoot* root,
    structCycle* cycle,
    CFocalLaw*,
    CFocalLaw*)
{
    if (step != eWriteHW_Leave)
    {
        return;
    }

    if (!root || !cycle)
    {
        return;
    }

    // Optional safety: ignore callbacks from another device.
    if (device_.get() != hw)
    {
        return;
    }

    Handler localHandler;
    {
        std::lock_guard lock(mutex_);
        if (!registered_)
        {
            return;
        }
        localHandler = handler_;
    }

    if (!localHandler)
    {
        return;
    }

    ConfigSnapshot snapshot;
    snapshot.fileName = fileName ? fileName : L"";
    snapshot.cycleCount = root->iCycleCount;
    snapshot.ascanEnabled = root->bAscanEnable != 0;

    snapshot.cycles.reserve(static_cast<std::size_t>(root->iCycleCount));

    for (int i = 0; i < root->iCycleCount; ++i)
    {
        snapshot.cycles.push_back(ConfigCycleSnapshot{ .cycle = i,
            .start = cycle[i].dStart,
            .range = cycle[i].dRange,
            .pointCount = static_cast<int>(cycle[i].lPointCount) });
    }

    localHandler(std::move(snapshot));
}

} // namespace scanlab::config