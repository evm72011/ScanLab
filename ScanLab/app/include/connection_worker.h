#pragma once

#include <QObject>
#include <QString>

#include "device_type.h"

namespace scanlab::hardware {
class Device;
}

class ConnectionWorker : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionWorker(scanlab::hardware::Device* hardwareDevice,
                          QObject* parent = nullptr);

public slots:
    void connectDevice(DeviceType::Type type, const QString& address);
    void disconnectDevice();
    void resetDevice();

signals:
    void connectCompleted(int result, bool connected, QString statusCode);
    void disconnected(bool stillConnected);
    void resetCompleted();

private:
    scanlab::hardware::Device* hardwareDevice_ = nullptr;
};