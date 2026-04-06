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