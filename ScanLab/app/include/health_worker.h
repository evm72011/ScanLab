#pragma once

#include <QObject>
#include <QTimer>
#include <QVariantList>

#include "scanlab/hardware/device.h"
#include "scanlab/hardware/health_monitor.h"

class HealthWorker : public QObject
{
    Q_OBJECT

public:
    explicit HealthWorker(QObject* parent = nullptr);

public slots:
    void setHardwareDevice(scanlab::hardware::Device* device);
    void setIntervalMs(int value);
    void start();
    void stop();

signals:
    void temperatureUpdated(int maxTemperature, QVariantList temperatures);

private slots:
    void poll();

private:
    scanlab::hardware::Device* hardwareDevice_ = nullptr;
    scanlab::hardware::HealthMonitor monitor_;
    QTimer* timer_ = nullptr;
    int intervalMs_ = 2000;
};