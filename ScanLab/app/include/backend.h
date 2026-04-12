#pragma once

#include <QObject>
#include <QString>

#include "runtime/device/device_context.h"
#include "ui/connection/connection_facade.h"
#include "ui/health/temperature_facade.h"
#include "ui/health/humidity_facade.h"

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ConnectionFacade* connectionFacade READ connectionFacade CONSTANT)
    Q_PROPERTY(TemperatureFacade* temperatureFacade READ temperatureFacade CONSTANT)
    Q_PROPERTY(HumidityFacade* humidityFacade READ humidityFacade CONSTANT)
public:
    explicit Backend(QObject* parent = nullptr);

    ConnectionFacade* connectionFacade();
    TemperatureFacade* temperatureFacade();
    HumidityFacade* humidityFacade();

private:
    DeviceContext context_;
    ConnectionFacade connectionFacade_{context_, this};
    TemperatureFacade temperatureFacade_{context_, this};
    HumidityFacade humidityFacade_{context_, this};
};
