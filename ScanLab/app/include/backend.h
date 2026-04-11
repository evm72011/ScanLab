#pragma once

#include <QObject>
#include <QString>

#include "runtime/device/device_context.h"
#include "ui/connection/connection_facade.h"
#include "ui/health/health_facade.h"

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ConnectionFacade* connectionFacade READ connectionFacade CONSTANT)
    Q_PROPERTY(HealthFacade* healthFacade READ healthFacade CONSTANT)

    // Deprecated
    //Q_PROPERTY(DeviceFacade* device READ device CONSTANT)
    //Q_PROPERTY(HealthMonitor* healthMonitor READ healthMonitor CONSTANT)

public:
    explicit Backend(QObject* parent = nullptr);

    ConnectionFacade* connectionFacade() { return &connectionFacade_; }
    HealthFacade* healthFacade() { return &healthFacade_; }

private:
    DeviceContext context_;
    ConnectionFacade connectionFacade_{context_, this};
    HealthFacade healthFacade_{context_, this};
};
