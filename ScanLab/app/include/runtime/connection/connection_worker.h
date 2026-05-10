#pragma once

#include <QObject>
#include <QString>

#include "runtime/connection/connection_service.h"
#include "runtime/device/device_type.h"
#include "runtime/errors/error_info.h"
#include "runtime/shell/shell_services.h"

class DeviceContext;

class ConnectionWorker : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionWorker(DeviceContext& context,
        ShellServices& shellServices,
        QObject* parent = nullptr);

public slots:
    void connect(DeviceType type, const QString& address);
    void disconnect();

signals:
    void connectionSucces(const ConnectionResult& value);
    void connectionFailure();
    void errorInfo(const ErrorInfo& value);
    void disconnectCompleted(bool stillConnected);

private:
    ToastService& toastService_;
    ConnectionService service_;
};
