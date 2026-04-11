#pragma once

#include <QObject>
#include <QString>

#include "runtime/device/device_type.h"
#include "runtime/connection/connection_service.h"

class DeviceContext;

class ConnectionWorker : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionWorker(DeviceContext& context, QObject* parent = nullptr);

public slots:
    void connect(DeviceType2 type, const QString& address);
    void disconnect();

signals:
    void connectionSucces();
    void connectionFailure();
    void connectionErrorCode(const QString& value);
    void disconnectCompleted(bool stillConnected);

private:
    ConnectionService service_;
};
