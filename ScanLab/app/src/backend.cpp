#include <Windows.h>

#include <UTDriverOEMPA.h>
#include <UTDriverOEMPAExport.h>
#include <UTDriverOEMPAmax.h>

#include "backend.h"

#include <QDebug>

Backend::Backend(QObject* parent)
    : QObject(parent)
{
    qDebug() << "startWatching()";
    configCallbackFacade_.startWatching();


    // if there is a lot of connection, pack them in a new class BackendCoordinator / BackendOrchestrator
    connect(
        &connectionFacade_,
        &ConnectionFacade::connectionStateChanged,
        this,
        [this]() {
            if (connectionFacade_.connectionState() == ConnectionState::State::Connected) {
//                qDebug() << "startWatching()";
//                configCallbackFacade_.startWatching();

                QTimer::singleShot(1000, this, [this]() {
                    qDebug() << "loadSelectedConfigFile: "  << configFileFacade_.selectedConfigFile();
                    configFileFacade_.loadSelectedConfigFile();
                });

                //configFileFacade_.loadSelectedConfigFile();
                //acquisitionConfigurationFacade_.refresh();
            }
        });

    connect(
        &configCallbackFacade_,
        &ConfigCallbackFacade::configSnapshotChanged,
        this,
        [this]() {
            qDebug() << "CONFIG CALLBACK:"
                     << configCallbackFacade_.configSnapshot();
        });
}

AppInfo* Backend::appInfo()
{
    return &appInfo_;
}

ConnectionFacade* Backend::connectionFacade()
{
    return &connectionFacade_;
}

AcquisitionConfigurationFacade* Backend::acquisitionConfigurationFacade()
{
    return &acquisitionConfigurationFacade_;
}

AScanFacade* Backend::ascanFacade()
{
    return &ascanFacade_;
}

ConfigCallbackFacade* Backend::configCallbackFacade()
{
    return &configCallbackFacade_;
}

ConfigFileFacade* Backend::configFileFacade()
{
    return &configFileFacade_;
}

TemperatureFacade* Backend::temperatureFacade()
{
    return &temperatureFacade_;
}

HumidityFacade* Backend::humidityFacade()
{
    return &humidityFacade_;
}
