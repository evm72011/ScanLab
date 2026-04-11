#include <Windows.h>

#include <UTDriverOEMPA.h>
#include <UTDriverOEMPAExport.h>
#include <UTDriverOEMPAmax.h>

#include "backend.h"

#include <QDebug>

Backend::Backend(QObject* parent)
    : QObject(parent)
{
}

ConnectionFacade* Backend::connectionFacade()
{
    return &connectionFacade_;
}

HealthFacade* Backend::healthFacade()
{
    return &healthFacade_;
}
