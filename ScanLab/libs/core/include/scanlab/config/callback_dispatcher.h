#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include "scanlab/config/config_snapshot.h"

#include <functional>
#include <mutex>

class CHWDeviceOEMPA;
class CFocalLaw;
struct structCorrectionOEMPA;
struct structRoot;
struct structCycle;
enum enumStepCustomizedAPI;

//using enumStepCustomizedAPI = int;

namespace scanlab::config {

class CallbackDispatcher {
public:
    using Handler = std::function<void(ConfigSnapshot)>;

    static CallbackDispatcher& instance();

    void registerCallback();
    void unregisterCallback();

    void setHandler(Handler handler);
    void clearHandler();

private:
    CallbackDispatcher() = default;

    static structCorrectionOEMPA* WINAPI callback(
        CHWDeviceOEMPA* hw,
        const wchar_t* fileName,
        enumStepCustomizedAPI step,
        structRoot* root,
        structCycle* cycle,
        CFocalLaw* emission,
        CFocalLaw* reception);

    void handle(
        const wchar_t* fileName,
        enumStepCustomizedAPI step,
        structRoot* root,
        structCycle* cycle,
        CFocalLaw* emission,
        CFocalLaw* reception);

    std::mutex mutex_;
    Handler handler_;
};

} // namespace scanlab::config