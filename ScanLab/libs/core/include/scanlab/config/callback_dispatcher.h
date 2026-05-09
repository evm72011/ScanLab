#pragma once

//#ifdef _WIN32
//#include <windows.h>
//#endif

#include "scanlab/config/config_snapshot.h"
#include "scanlab/device/device.h"

#include <functional>
#include <mutex>

class CHWDeviceOEMPA;
class CFocalLaw;
struct structCorrectionOEMPA;
struct structRoot;
struct structCycle;
enum enumStepCustomizedAPI;

namespace scanlab::config
{

class CallbackDispatcher
{
public:
    using Handler = std::function<void(ConfigSnapshot)>;

    explicit CallbackDispatcher(scanlab::device::Device& device);
    ~CallbackDispatcher();

    CallbackDispatcher(const CallbackDispatcher&) = delete;
    CallbackDispatcher& operator=(const CallbackDispatcher&) = delete;

    void registerCallback();
    void unregisterCallback();

    void setHandler(Handler handler);
    void clearHandler();

private:
    static structCorrectionOEMPA* WINAPI callback(CHWDeviceOEMPA* hw,
        const wchar_t* fileName,
        enumStepCustomizedAPI step,
        structRoot* root,
        structCycle* cycle,
        CFocalLaw* emission,
        CFocalLaw* reception);

    void handle(CHWDeviceOEMPA* hw,
        const wchar_t* fileName,
        enumStepCustomizedAPI step,
        structRoot* root,
        structCycle* cycle,
        CFocalLaw* emission,
        CFocalLaw* reception);

private:
    scanlab::device::Device& device_;

    std::mutex mutex_;
    Handler handler_;
    bool registered_ = false;
};

} // namespace scanlab::config