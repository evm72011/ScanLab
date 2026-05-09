#include "scanlab/device/device_lock_guard.h"

#include <UTDriverOEMPA.h>
#include <Windows.h>

DeviceLockGuard::DeviceLockGuard(CHWDeviceOEMPA& hw)
    : DeviceLockGuard(hw, eAcqDefault, eAcqDefault)
{
}

DeviceLockGuard::DeviceLockGuard(CHWDeviceOEMPA& hw,
    enumAcquisitionState eAcqLockState,
    enumAcquisitionState eAcqUnlockState)
    : hw_(hw)
    , eAcqUnlockState_(eAcqUnlockState)
{
    locked_ = hw_.LockDevice(eAcqLockState);
}

bool DeviceLockGuard::locked() const
{
    return locked_;
}

bool DeviceLockGuard::release()
{
    if (locked_)
    {
        locked_ = !hw_.UnlockDevice(eAcqUnlockState_);
        ;
    }
    return !locked_;
}

DeviceLockGuard::~DeviceLockGuard()
{
    if (locked_)
    {
        hw_.UnlockDevice(eAcqUnlockState_);
    }
}
