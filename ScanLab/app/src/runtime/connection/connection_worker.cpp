#include "runtime/connection/connection_worker.h"

#include "runtime/device/device_context.h"
#include "runtime/connection/connection_service.h"
#include <magic_enum/magic_enum.hpp>

ConnectionWorker2::ConnectionWorker2(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
}

void ConnectionWorker2::connect(DeviceType2 type, const QString& address)
{
    const auto connectionResult = service_.connect(type, address.toStdWString());
    if (!connectionResult.has_value()) {
        const auto error = connectionResult.error();
        const auto errorCode = QString::fromUtf8(magic_enum::enum_name(error).data());
        emit connectionErrorCode(errorCode);
        emit connectionFailure();
        return;
    }
    emit connectionSucces();
}

void ConnectionWorker2::disconnect()
{
    service_.disconnect();
    const auto stillConnected = service_.isConnected();
    emit disconnectCompleted(stillConnected);
}
