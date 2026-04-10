#include "runtime/health/health_service.h"
#include "runtime/device/device_context.h"

#include "scanlab/hardware/temperature_reader.h"

HealthService::HealthService(DeviceContext& context)
    : context_(context)
    , temperatureReader_(std::make_unique<scanlab::hardware::TemperatureReader>(*context.device()))
{
}

std::expected<int, scanlab::hardware::TemperatureErrorCodes> HealthService::readMax() const {
    return temperatureReader_->readMax();
}

HealthService::~HealthService() = default;
