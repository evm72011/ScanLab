#pragma once

#include "runtime/device/device_type_def.h"

enum class DeviceType
{
#define X(name) name,
    DEVICE_TYPE_LIST(X)
#undef X
};
