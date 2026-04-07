#pragma once

#include <QObject>

#include "runtime/health/health_service.h"

class DeviceContext;

class HealthWorker2 : public QObject
{
    Q_OBJECT

public:
    explicit HealthWorker2(DeviceContext& context, QObject* parent = nullptr);
private:
    HealthService service_;
};
