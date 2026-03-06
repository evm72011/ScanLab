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
        OEMPAMax = 0,
        OEMPAMini
    };
    Q_ENUM(Type)
};
