#include "runtime/health/health_service.h"
#include "runtime/device/device_context.h"

#include "scanlab/hardware/temperature_reader.h"

HealthService::HealthService(DeviceContext& context)
    : context_(context)
    , temperatureReader_(std::make_unique<scanlab::hardware::TemperatureReader>(*context.device()))
{
}

std::optional<scanlab::hardware::TemperatureSnapshot> HealthService::readTemperature() const {
    return temperatureReader_->read();
}

HealthService::~HealthService() = default;
