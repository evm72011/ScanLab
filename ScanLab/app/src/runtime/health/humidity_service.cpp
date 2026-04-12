#include "runtime/health/humidity_service.h"
#include "runtime/device/device_context.h"

#include "scanlab/hardware/health/humidity_reader.h"

HumidityService::HumidityService(DeviceContext& context)
    : context_(context)
    , humidityReader_(std::make_unique<scanlab::hardware::HumidityReader>(*context.device()))
{
}

std::expected<int, scanlab::hardware::HealthErrorCodes> HumidityService::readMax() const {
    return humidityReader_->readMax();
}

HumidityService::~HumidityService() = default;
