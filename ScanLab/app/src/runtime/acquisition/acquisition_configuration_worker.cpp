#include "runtime/acquisition/acquisition_configuration_worker.h"

#include "runtime/device/device_context.h"

#include <magic_enum/magic_enum.hpp>

namespace sa = scanlab::acquisition;

AcquisitionConfigurationWorker::AcquisitionConfigurationWorker(DeviceContext& context,
    QObject* parent)
    : QObject(parent)
    , service_(context)
{
}

void AcquisitionConfigurationWorker::readCycleCount()
{
    const auto cycleCount = service_.readCycleCount();

    if (!cycleCount.has_value())
    {
        const auto error = cycleCount.error();
        const auto errorCode = std::
            visit([](const auto
                          value) { return QString::fromUtf8(magic_enum::enum_name(value).data()); },
                error);

        emit acquisitionConfigurationErrorCode(errorCode);
        emit acquisitionConfigurationUnavailable();
        return;
    }

    emit cycleCountUpdated(*cycleCount);
}

void AcquisitionConfigurationWorker::readAscanParameters(int cycle)
{
    const auto parameters = service_.readAscanParameters(cycle);

    if (!parameters.has_value())
    {
        const auto error = parameters.error();
        const auto errorCode = std::
            visit([](const auto
                          value) { return QString::fromUtf8(magic_enum::enum_name(value).data()); },
                error);

        emit acquisitionConfigurationErrorCode(errorCode);
        emit acquisitionConfigurationUnavailable();
        return;
    }

    emit ascanParametersUpdated(*parameters);
}

void AcquisitionConfigurationWorker::writeAscanParameters(sa::AscanParameters parameters)
{
    const auto result = service_.writeAscanParameters(parameters);

    if (!result.has_value())
    {
        const auto error = result.error();
        const auto errorCode = std::
            visit([](const auto
                          value) { return QString::fromUtf8(magic_enum::enum_name(value).data()); },
                error);

        emit acquisitionConfigurationErrorCode(errorCode);
        emit acquisitionConfigurationUnavailable();
        return;
    }

    emit writeCompleted();
}