#include "runtime/health/temperature_worker.h"

#include "runtime/device/device_context.h"

#include <magic_enum/magic_enum.hpp>

TemperatureWorker::TemperatureWorker(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
}

void TemperatureWorker::pollMaxTemperature()
{
    const auto maxTemperature = service_.readMax();
    if (!maxTemperature.has_value())
    {
        const auto error = maxTemperature.error();
        const auto errorCode = std::visit(
            [](const auto value) { return QString::fromUtf8(magic_enum::enum_name(value).data()); },
            error);
        emit maxTemperatureErrorCode(errorCode);
        emit maxTemperatureUnavailable();
        return;
    }

    emit maxTemperatureUpdated(*maxTemperature);
}