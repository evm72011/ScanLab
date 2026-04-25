#include "runtime/acquisition/acquisition_configuration_service.h"
#include "runtime/device/device_context.h"

namespace sa = scanlab::acquisition;

AcquisitionConfigurationService::AcquisitionConfigurationService(DeviceContext& context)
    : context_(context)
    , configurator_(std::make_unique<sa::AcquisitionConfigurator>(*context.device()))
{
}

AcquisitionConfigurationService::~AcquisitionConfigurationService() = default;

std::expected<int, sa::AcquisitionError>
AcquisitionConfigurationService::readCycleCount() const
{
    return configurator_->getCycleCount();
}

std::expected<sa::AscanParameters, sa::AcquisitionError>
AcquisitionConfigurationService::readAscanParameters(int cycle) const
{
    return configurator_->getAscanParameters(cycle);
}

std::expected<void, sa::AcquisitionError>
AcquisitionConfigurationService::writeAscanParameters(
    const sa::AscanParameters& parameters)
{
    return configurator_->setAscanParameters(parameters);
}