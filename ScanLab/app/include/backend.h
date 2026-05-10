#pragma once

#include <QObject>
#include <QString>

#include "runtime/device/device_context.h"
#include "ui/acquisition/acquisition_configuration_facade.h"
#include "ui/acquisition/ascan_facade.h"
#include "ui/app_info.h"
#include "ui/config/config_callback_facade.h"
#include "ui/config/config_file_facade.h"
#include "ui/connection/connection_facade.h"
#include "ui/health/humidity_facade.h"
#include "ui/health/temperature_facade.h"
#include "ui/shell/toast/toast_facade.h"

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ToastFacade* toastFacade READ toastFacade CONSTANT)
    Q_PROPERTY(AppInfo* appInfo READ appInfo CONSTANT)
    Q_PROPERTY(ConnectionFacade* connectionFacade READ connectionFacade CONSTANT)
    Q_PROPERTY(AcquisitionConfigurationFacade* acquisitionConfigurationFacade READ
            acquisitionConfigurationFacade CONSTANT)
    Q_PROPERTY(AScanFacade* ascanFacade READ ascanFacade CONSTANT)
    Q_PROPERTY(ConfigCallbackFacade* configCallbackFacade READ configCallbackFacade CONSTANT)
    Q_PROPERTY(ConfigFileFacade* configFileFacade READ configFileFacade CONSTANT)
    Q_PROPERTY(TemperatureFacade* temperatureFacade READ temperatureFacade CONSTANT)
    Q_PROPERTY(HumidityFacade* humidityFacade READ humidityFacade CONSTANT)
public:
    explicit Backend(QObject* parent = nullptr);

    ToastFacade* toastFacade();
    AppInfo* appInfo();
    ConnectionFacade* connectionFacade();
    AcquisitionConfigurationFacade* acquisitionConfigurationFacade();
    AScanFacade* ascanFacade();
    ConfigCallbackFacade* configCallbackFacade();
    ConfigFileFacade* configFileFacade();
    TemperatureFacade* temperatureFacade();
    HumidityFacade* humidityFacade();

private:
    ToastFacade toastFacade_{ this };

    DeviceContext context_;
    AppInfo appInfo_;
    ConnectionFacade connectionFacade_{ context_, toastFacade_, this };
    AcquisitionConfigurationFacade acquisitionConfigurationFacade_{ context_, this };
    AScanFacade ascanFacade_{ context_, this };
    ConfigCallbackFacade configCallbackFacade_{ context_, this };
    ConfigFileFacade configFileFacade_{ context_, this };
    TemperatureFacade temperatureFacade_{ context_, this };
    HumidityFacade humidityFacade_{ context_, this };
};
