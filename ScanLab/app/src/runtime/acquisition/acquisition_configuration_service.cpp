#include "runtime/acquisition/acquisition_configuration_service.h"
#include "scanlab/acquisition/customized_api_dispatcher.h"
#include "runtime/device/device_context.h"

namespace sa = scanlab::acquisition;

AcquisitionConfigurationService::AcquisitionConfigurationService(DeviceContext& context)
    : context_(context)
    , configurator_(std::make_unique<sa::AcquisitionConfigurator>(
          *context.device(),
          context.setupSnapshot()))
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
    const sa::AscanParameters testParameters{
        .cycle = cycle,
        .start = 5.0e-6,      // сдвиг начала вправо на 5 µs
        .range = 30.0e-6,     // ширина окна
        .pointCount = 512
    };

    auto writeResult = configurator_->setAscanParameters(testParameters);
    if (!writeResult) {
        return std::unexpected(writeResult.error());
    }

    return configurator_->getAscanParameters(cycle);

    /*
    auto* hw = context_.device()->get();
    if (!hw) {
        return std::unexpected(sa::AcquisitionErrorKind::ReadParameterFailed);
    }

    sa::CustomizedApiDispatcher::registerSnapshot(
        hw,
        &context_.setupSnapshot());

    // TEMP: because callback has not populated snapshot yet
    context_.setupSnapshot().updateOne(sa::AscanParameters{
        .cycle = cycle,
        .start = 0.0,
        .range = 30.0e-6,
        .pointCount = 512
    });

    return configurator_->getAscanParameters(cycle);
    */
}

std::expected<void, sa::AcquisitionError>
AcquisitionConfigurationService::writeAscanParameters(
    const sa::AscanParameters& parameters)
{
    return configurator_->setAscanParameters(parameters);
}