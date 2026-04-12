#include "runtime/health/humidity_worker.h"

#include "runtime/device/device_context.h"

#include <magic_enum/magic_enum.hpp>

HumidityWorker::HumidityWorker(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
}

void HumidityWorker::pollMaxHumidity()
{
    const auto maxHumidity = service_.readMax();
    if (!maxHumidity.has_value()) {
        const auto error = maxHumidity.error();
        const auto errorCode = QString::fromUtf8(magic_enum::enum_name(error).data());
        emit maxHumidityErrorCode(errorCode);
        emit maxHumidityUnavailable();
        return;
    }

    emit maxHumidityUpdated(*maxHumidity);
}
