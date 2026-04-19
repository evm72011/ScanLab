#include "runtime/health/humidity_service.h"
#include "runtime/device/device_context.h"

#include "scanlab/health/humidity_reader.h"

namespace sh = scanlab::health;

HumidityService::HumidityService(DeviceContext& context)
    : context_(context)
    , humidityReader_(std::make_unique<sh::HumidityReader>(*context.device()))
{
}

std::expected<int, sh::HealthError> HumidityService::readMax() const {
    return humidityReader_->readMax();
}

HumidityService::~HumidityService() = default;
