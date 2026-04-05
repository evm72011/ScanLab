#pragma once

#include <QObject>
#include <QPointer>
#include <QThread>
#include <QVariantList>
#include <qqmlintegration.h>

#include "device_facade.h"

class HealthWorker;

class HealthMonitor : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(DeviceFacade* device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(bool hasTemperature READ hasTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(int maxTemperature READ maxTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(QVariantList temperatures READ temperatures NOTIFY temperatureChanged)
    Q_PROPERTY(int intervalMs READ intervalMs WRITE setIntervalMs NOTIFY intervalMsChanged)

public:
    explicit HealthMonitor(QObject* parent = nullptr);
    ~HealthMonitor() override;

    DeviceFacade* device() const;
    void setDevice(DeviceFacade* value);

    bool hasTemperature() const;
    int maxTemperature() const;
    QVariantList temperatures() const;

    int intervalMs() const;
    void setIntervalMs(int value);

signals:
    void deviceChanged();
    void temperatureChanged();
    void intervalMsChanged();

private:
    void clearTemperatureState();
    void syncWorkerState();

private:
    QPointer<DeviceFacade> device_;

    int maxTemperature_ = -1;
    QVariantList temperatures_;
    int intervalMs_ = 2000;

    QThread workerThread_;
    HealthWorker* worker_ = nullptr;
};