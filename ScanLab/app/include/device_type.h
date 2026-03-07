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
        OEMPAMax,
        OEMPAMini
    };
    Q_ENUM(Type)
};
