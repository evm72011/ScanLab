#pragma once

#include <QObject>
#include <QString>

#include "runtime/health/temperature_service.h"

class DeviceContext;

class TemperatureWorker : public QObject
{
    Q_OBJECT

public:
    explicit TemperatureWorker(DeviceContext& context, QObject* parent = nullptr);

public slots:
    void pollMaxTemperature();

signals:
    void maxTemperatureUpdated(int value);
    void maxTemperatureUnavailable();
    void maxTemperatureErrorCode(const QString& value);

private:
    TemperatureService service_;
};
