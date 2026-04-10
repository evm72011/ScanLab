#pragma once

#include <QObject>
#include <QString>

#include "runtime/health/health_service.h"

class DeviceContext;

class HealthWorker2 : public QObject
{
    Q_OBJECT

public:
    explicit HealthWorker2(DeviceContext& context, QObject* parent = nullptr);

public slots:
    void pollMaxTemperature();

signals:
    void maxTemperatureUpdated(int value);
    void maxTemperatureUnavailable();
    void maxTemperatureErrorCode(const QString& value);

private:
    HealthService service_;
};
