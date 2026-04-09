#pragma once

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QVariantList>
#include <qqmlintegration.h>

#include "scanlab/hardware/temperature_types.h"

class DeviceContext;
class HealthWorker2;

class HealthFacade : public QObject
{
    Q_OBJECT
    // QML_ELEMENT

    Q_PROPERTY(bool temperatureUnavailable READ temperatureUnavailable NOTIFY temperatureUnavailableChanged)
    Q_PROPERTY(int maxTemperature READ maxTemperature NOTIFY temperatureSnapshotChanged)
    Q_PROPERTY(bool hasTemperature READ hasTemperature NOTIFY temperatureSnapshotChanged)
    Q_PROPERTY(QVariantList temperatures READ temperatures NOTIFY temperatureSnapshotChanged)

public:
    explicit HealthFacade(DeviceContext& context, QObject* parent = nullptr);
    ~HealthFacade() override;

    bool temperatureUnavailable() const;
    int maxTemperature() const;
    bool hasTemperature() const;
    QVariantList temperatures() const;

    Q_INVOKABLE void startPolling();
    Q_INVOKABLE void stopPolling();

signals:
    void requestPoll();
    void temperatureUnavailableChanged();
    void temperatureSnapshotChanged();

private:
    void poll();
    void setTemperatureSnapshot(scanlab::hardware::TemperatureSnapshot value);
    void setTemperatureUnavailable(bool value);

private:
    QTimer timer_;
    int interval_ = 2000;

    scanlab::hardware::TemperatureSnapshot temperatureSnapshot_;
    bool temperatureUnavailable_ = true;

    HealthWorker2* worker_ = nullptr;
    QThread workerThread_;
};