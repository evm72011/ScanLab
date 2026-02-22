#pragma once

#include <QObject>
#include <QString>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    explicit Backend(QObject *parent = nullptr);

    Q_INVOKABLE bool connectDevice(const QString& address);
    bool connected() const { return connected_; }
signals:
    void connectedChanged();
private:
    bool connected_ = false;

    // TODO: твой реальный указатель/объект устройства из OEMPA
    // HWDeviceOEMPA* m_pHWDeviceOEMPA = nullptr;

    // В упрощённом варианте просто “проверяем что объект есть”
    bool ensureDeviceCreated();
};
