#pragma once

#include <QObject>
#include <qqmlintegration.h>

class ConnectionState : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Enum only")

public:
    enum State {
        Disconnected = 0,
        Connecting,
        Connected,
        Disconnecting
    };
    Q_ENUM(State)
};
