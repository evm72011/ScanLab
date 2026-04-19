#pragma once

#include "runtime/acquisition/ascan/ascan_service.h"

#include <QObject>

class DeviceContext;

class AScanWorker : public QObject
{
    Q_OBJECT

public:
    explicit AScanWorker(DeviceContext& context, QObject* parent = nullptr);

public slots:
    void start();
    void stop();

signals:
    void frameUpdated(scanlab::acquisition::ascan::Frame frame);
    void started();
    void startFailed();
    void stopped(bool stillRunning);

private:
    AScanService service_;
};