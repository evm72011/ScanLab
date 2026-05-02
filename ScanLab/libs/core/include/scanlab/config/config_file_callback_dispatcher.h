#pragma once

#include "scanlab/config/config_snapshot.h"

#include <functional>
#include <mutex>

class CHWDeviceOEMPA;
class CFocalLaw;
struct structCorrectionOEMPA;
struct structRoot;
struct structCycle;
enum enumStepCustomizedAPI;

namespace scanlab::config {

class ConfigFileCallbackDispatcher {
public:
    using Handler = std::function<void(ConfigSnapshot)>;

    static ConfigFileCallbackDispatcher& instance();

    void registerCallback();
    void unregisterCallback();

    void setHandler(Handler handler);
    void clearHandler();

private:
    ConfigFileCallbackDispatcher() = default;

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