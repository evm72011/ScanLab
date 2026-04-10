#include "runtime/health/health_worker.h"

#include "runtime/device/device_context.h"

#include <magic_enum/magic_enum.hpp>

HealthWorker2::HealthWorker2(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
}

void HealthWorker2::pollMaxTemperature()
{
    const auto maxTemperature = service_.readMax();
    if (!maxTemperature.has_value()) {
        const auto error = maxTemperature.error();
        const auto errorCode = QString::fromUtf8(magic_enum::enum_name(error).data());
        emit maxTemperatureErrorCode(errorCode);
        emit maxTemperatureUnavailable();
        return;
    }

    emit maxTemperatureUpdated(*maxTemperature);
}