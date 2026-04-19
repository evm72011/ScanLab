#include "runtime/health/temperature_service.h"
#include "runtime/device/device_context.h"

#include "scanlab/health/temperature_reader.h"

namespace sh = scanlab::health;

TemperatureService::TemperatureService(DeviceContext& context)
    : context_(context)
    , temperatureReader_(std::make_unique<sh::TemperatureReader>(*context.device()))
{
}

std::expected<int, sh::HealthError> TemperatureService::readMax() const {
    return temperatureReader_->readMax();
}

TemperatureService::~TemperatureService() = default;
