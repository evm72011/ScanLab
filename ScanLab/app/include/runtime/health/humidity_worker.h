#pragma once

#include <QObject>
#include <QString>

#include "runtime/health/humidity_service.h"

class DeviceContext;

class HumidityWorker : public QObject
{
    Q_OBJECT

public:
    explicit HumidityWorker(DeviceContext& context, QObject* parent = nullptr);

public slots:
    void pollMaxHumidity();

signals:
    void maxHumidityUpdated(int value);
    void maxHumidityUnavailable();
    void maxHumidityErrorCode(const QString& value);

private:
    HumidityService service_;
};
