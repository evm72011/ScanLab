#include "runtime/connection/connection_worker.h"

#include "runtime/device/device_context.h"
#include "runtime/connection/connection_service.h"
#include <magic_enum/magic_enum.hpp>

ConnectionWorker::ConnectionWorker(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
}

void ConnectionWorker::connect(DeviceType type, const QString& address)
{
    const auto connectionResult = service_.connect(type, address.toStdWString());
    if (!connectionResult.has_value()) {
        const auto& error = connectionResult.error();
        const auto errorInfo = describeError(error);

        if (errorInfo.textKey) {
            emit connectionErrorCode(errorInfo.textKey);
        }
        else {
            emit connectionErrorCode(errorInfo.fallbackText);
        }
        emit connectionFailure();
        return;
    }
    emit connectionSucces(*connectionResult);
}

void ConnectionWorker::disconnect()
{
    service_.disconnect();
    const auto stillConnected = service_.isConnected();
    emit disconnectCompleted(stillConnected);
}
