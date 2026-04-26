#pragma once

#include "scanlab/acquisition/acquisition_setup_snapshot.h"
#include <Windows.h>
#include <UTDriverOEMPA.h>
#include <UTDriverOEMPA1.h>
#include <CustomizedDriverOEMPA1.h>

namespace scanlab::acquisition {

class CustomizedApiDispatcher {
public:
    static void registerSnapshot(
        CHWDeviceOEMPA* device,
        AcquisitionSetupSnapshot* snapshot);

    static void unregisterSnapshot(CHWDeviceOEMPA* device);

private:
    static structCorrectionOEMPA* WINAPI callback(
        CHWDeviceOEMPA* device,
        const wchar_t* fileName,
        enumStepCustomizedAPI step,
        structRoot* root,
        structCycle* cycle,
        CFocalLaw* emission,
        CFocalLaw* reception);
};

} // namespace scanlab::acquisition