#include <Windows.h>

#include <UTDriverOEMPA.h>
#include <UTDriverOEMPAExport.h>
#include <UTDriverOEMPAmax.h>

#include "backend.h"

#include <QDebug>

Backend::Backend(QObject* parent)
    : QObject(parent)
{
    // if there is a lot of connection, pack them in a new class BackendCoordinator / BackendOrchestrator
    connect(
        &connectionFacade_,
        &ConnectionFacade::connectionStateChanged,
        this,
        [this]() {
            if (connectionFacade_.connectionState() == ConnectionState::State::Connected) {
                acquisitionConfigurationFacade_.refresh();
            }
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

TemperatureFacade* Backend::temperatureFacade()
{
    return &temperatureFacade_;
}

HumidityFacade* Backend::humidityFacade()
{
    return &humidityFacade_;
}
