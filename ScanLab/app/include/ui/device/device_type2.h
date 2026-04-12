// device_type2_qml.h
#pragma once

#include <QObject>
#include <qqmlintegration.h>
#include "runtime/device/device_type_def.h"

class DeviceTypeQml : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Enum only")

public:
    enum Type {
#define X(name) name,
        DEVICE_TYPE_LIST(X)
#undef X
    };
    Q_ENUM(Type)
};
