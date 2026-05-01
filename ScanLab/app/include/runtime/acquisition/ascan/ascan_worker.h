#pragma once

#include "runtime/acquisition/ascan/ascan_service.h"

#include <QObject>
#include <QtTypes>

class DeviceContext;

class AScanWorker : public QObject
{
    Q_OBJECT

public:
    explicit AScanWorker(DeviceContext& context, QObject* parent = nullptr);

public slots:
    void start();
    void stop();
    void setCycleFilter(int cycle);
    void setCropMargins(qreal leftFraction, qreal rightFraction);

signals:
    void frameUpdated(scanlab::acquisition::ascan::Frame frame);
    void started();
    void startFailed();
    void stopped(bool stillRunning);

private:
    AScanService service_;
};