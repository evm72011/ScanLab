#include "backend.h"
#include <QDebug>

Backend::Backend(QObject *parent)
    : QObject(parent)
{
}

bool Backend::ensureDeviceCreated()
{
    // TODO: здесь должна быть реальная инициализация OEMPA устройства.
    // Примерно:
    // if (!m_pHWDeviceOEMPA) m_pHWDeviceOEMPA = CreateHwDevice(...);

    // Пока заглушка:
    return false;
}

bool Backend::connectDevice(const QString& address)
{
    if (!ensureDeviceCreated()) {
        qWarning() << "OEMPA device not created";
        return false;
    }

    // Преобразование QString -> wchar_t*
    const std::wstring waddr = address.toStdWString();
    const wchar_t* pValue = waddr.c_str();

    // === ЭТО 1:1 логика из твоего MFC кода ===
    // bool ok =
    //     m_pHWDeviceOEMPA->GetSWDeviceOEMPA()->SetAddress(pValue) &&
    //     m_pHWDeviceOEMPA->GetSWDevice()->SetConnectionState(eConnected, true);

    bool ok = true; // <- временно, пока не подключил реальные вызовы

    if (!ok) {
        qWarning() << "connectDevice failed for" << address;
        connected_ = false;
        emit connectedChanged();
        return false;
    }

    connected_ = true;
    emit connectedChanged();
    qInfo() << "Connected to" << address;
    return true;
}
