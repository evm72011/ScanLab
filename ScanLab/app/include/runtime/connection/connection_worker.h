#pragma once

#include <QObject>
#include <QString>

#include "runtime/device/device_type.h"
#include "runtime/connection/connection_result.h"
#include "runtime/connection/connection_service.h"

class DeviceContext;

class ConnectionWorker2 : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionWorker2(DeviceContext& context, QObject* parent = nullptr);

public slots:
    void connectDevice(DeviceType2 type, const QString& address);
    void disconnectDevice();
    void resetDevice();

signals:
    void connectCompleted(ConnectionResult result);
    void disconnected(bool stillConnected);
    void resetCompleted();

private:
    ConnectionService service_;
};