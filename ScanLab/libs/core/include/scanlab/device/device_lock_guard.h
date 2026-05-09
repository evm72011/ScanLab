#pragma once

#include <UTBasicEnum.h>

class CHWDeviceOEMPA;

class DeviceLockGuard
{
public:
    explicit DeviceLockGuard(CHWDeviceOEMPA &hw);

    explicit DeviceLockGuard(CHWDeviceOEMPA &hw,
                             enumAcquisitionState eAcqLockState,
                             enumAcquisitionState eAcqUnlockState);

    ~DeviceLockGuard();

    bool locked() const;
    bool release();

private:
    CHWDeviceOEMPA &hw_;
    enumAcquisitionState eAcqUnlockState_;
    bool locked_ = false;
};
