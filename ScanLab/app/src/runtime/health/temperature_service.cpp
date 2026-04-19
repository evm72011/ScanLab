#include "runtime/health/temperature_service.h"
#include "runtime/device/device_context.h"

#include "scanlab/health/temperature_reader.h"

TemperatureService::TemperatureService(DeviceContext& context)
    : context_(context)
    , temperatureReader_(std::make_unique<scanlab::hardware::TemperatureReader>(*context.device()))
{
}

std::expected<int, scanlab::hardware::HealthError> TemperatureService::readMax() const {
    return temperatureReader_->readMax();
}

TemperatureService::~TemperatureService() = default;
