#pragma once

#include "runtime/acquisition/ascan/ascan_service.h"

#include "scanlab/acquisition/ascan/frame.h"

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
    void startFailed();
    void started();
    void stopped(bool stillRunning);

private:
    AScanService service_;
};