#include "runtime/connection/connection_worker.h"

#include "runtime/connection/connection_service.h"
#include "runtime/device/device_context.h"
#include <magic_enum/magic_enum.hpp>

ConnectionWorker::ConnectionWorker(DeviceContext& context,
    ShellServices& shellServices,
    QObject* parent)
    : QObject(parent)
    , toastService_(shellServices.toastService())
    , service_(context)
{
}

void ConnectionWorker::connect(DeviceType type, const QString& address)
{
    const auto connectionResult = service_.connect(type, address.toStdWString());
    if (connectionResult.has_value())
    {
        emit connectionSucces(*connectionResult);

        auto title = tr("Device").toStdString();
        auto text = tr("Successfully connected").toStdString();
        toastService_.showInfo(title, text);
        return;
    }

    const auto& error = connectionResult.error();
    const auto errorInfo_ = describeError(error);
    emit errorInfo(errorInfo_);
    emit connectionFailure();
}

void ConnectionWorker::disconnect()
{
    service_.disconnect();
    const auto stillConnected = service_.isConnected();
    emit disconnectCompleted(stillConnected);
}
