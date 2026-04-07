#include "runtime/connection/connection_worker.h"

#include "runtime/device/device_context.h"
#include "runtime/connection/connection_service.h"

ConnectionWorker2::ConnectionWorker2(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , service_(context)
{
}

void ConnectionWorker2::connectDevice(DeviceType2 type, const QString& address)
{
    const auto result = service_.connect(type, address.toStdWString());
    emit connectCompleted(result);
}

void ConnectionWorker2::disconnectDevice()
{
    service_.disconnect();
    emit disconnected(service_.isConnected());
}

void ConnectionWorker2::resetDevice()
{
    service_.disconnect();
    emit resetCompleted();
}