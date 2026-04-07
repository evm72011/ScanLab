/*
#pragma once

#include <QObject>

namespace SL
{
Q_NAMESPACE

enum ConnectionState2 {
    Disconnected = 0,
    Connecting,
    Connected
};
Q_ENUM_NS(ConnectionState2)

}
*/

#pragma once

#include <QObject>
#include <qqmlintegration.h>

class ConnectionState2 : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Enum only")

public:
    enum State {
        Disconnected = 0,
        Connecting,
        Connected
    };
    Q_ENUM(State)
};
