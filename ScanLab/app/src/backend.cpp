#include <Windows.h>

#include <memory>

#include <UTDriverOEMPA.h>
#include <UTDriverOEMPAExport.h>
#include <UTDriverOEMPAmax.h>

#include "backend.h"
#include <QDebug>


Backend::Backend(QObject *parent)
    : QObject(parent)
{
}

bool Backend::ensureDeviceCreated()
{
    return false;
}

bool Backend::connectDevice(const QString& address)
{
     qInfo() << "[1] start";

    auto hw = std::make_unique<CHWDeviceOEMPAmax>();
     qInfo() << "[2] device created";

    const wchar_t* addr = L"192.168.1.11";      // Ethernet
    // const wchar_t* addr = L"pcie://device=0"; // PCIe

    auto* swOempa = hw->GetSWDeviceOEMPA();
    if (!swOempa || !swOempa->SetAddress(addr)) {
         qInfo() << "[E] SetAddress failed";
        return false;
    }
     qInfo() << "[3] address set";

    // базовый слой — подключение
    auto* swBase = hw->GetSWDevice();
    if (!swBase || !swBase->SetConnectionState(eConnected, true)) {
         qInfo() << "[E] Connect failed";
        return false;
    }

     qInfo() << "[4] connected";

    return true;
}
