#include "scanlab/acquisition/customized_api_dispatcher.h"

#include "scanlab/acquisition/ascan_parameters.h"

#include <mutex>
#include <unordered_map>
#include <vector>

namespace scanlab::acquisition {
namespace {

std::mutex g_mutex;

std::unordered_map<CHWDeviceOEMPA*, AcquisitionSetupSnapshot*> g_snapshots;

} // namespace

void CustomizedApiDispatcher::registerSnapshot(
    CHWDeviceOEMPA* device,
    AcquisitionSetupSnapshot* snapshot)
{
    if (!device || !snapshot) {
        return;
    }

    {
        std::lock_guard lock(g_mutex);
        g_snapshots[device] = snapshot;
    }

    OEMPA_SetCallbackCustomizedDriverAPI(&CustomizedApiDispatcher::callback);
}

void CustomizedApiDispatcher::unregisterSnapshot(CHWDeviceOEMPA* device)
{
    if (!device) {
        return;
    }

    std::lock_guard lock(g_mutex);
    g_snapshots.erase(device);
}

structCorrectionOEMPA* WINAPI CustomizedApiDispatcher::callback(
    CHWDeviceOEMPA* device,
    const wchar_t*,
    enumStepCustomizedAPI step,
    structRoot* root,
    structCycle* cycle,
    CFocalLaw*,
    CFocalLaw*)
{
    if (step != eWriteHW_Leave || !device || !root || !cycle) {
        return nullptr;
    }

    if (root->iCycleCount <= 0) {
        return nullptr;
    }

    AcquisitionSetupSnapshot* snapshot = nullptr;

    {
        std::lock_guard lock(g_mutex);

        const auto it = g_snapshots.find(device);
        if (it == g_snapshots.end()) {
            return nullptr;
        }

        snapshot = it->second;
    }

    std::vector<AscanParameters> parameters;
    parameters.reserve(static_cast<std::size_t>(root->iCycleCount));

    for (int i = 0; i < root->iCycleCount; ++i) {
        parameters.push_back(AscanParameters{
            .cycle = i,
            .start = cycle[i].dStart,
            .range = cycle[i].dRange,
            .pointCount = static_cast<int>(cycle[i].lPointCount),
        });
    }

    const double digitizingPeriod =
        device->GetSWDeviceOEMPA()
            ? device->GetSWDeviceOEMPA()->dGetClockPeriod()
            : 0.0;

    snapshot->update(root->iCycleCount, digitizingPeriod, parameters);

    return nullptr;
}

} // namespace scanlab::acquisition