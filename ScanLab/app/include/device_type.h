#pragma once

#include <QObject>
#include <qqmlintegration.h>

class DeviceType : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Enum only")

public:
    enum Type {
        None = 0,
        OEMPA_1,
        OEMPA_2,
        OEMPA_Mini,
        OEMPA_Max,
        OEMPA_MC1,
        OEMPA_MC2,
        OEMPA_MCmu,
        OEMPA_MCmuF,
        OEMPA_Micro
    };
    Q_ENUM(Type)
};
