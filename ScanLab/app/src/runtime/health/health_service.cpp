#include "runtime/health/health_service.h"
#include "runtime/device/device_context.h"

HealthService::HealthService(DeviceContext& context)
    : context_(context)
{
}