//#ifndef BACKEND_H
//#define BACKEND_H

//#endif // BACKEND_H
#pragma once

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(QObject *parent = nullptr);

    Q_INVOKABLE void connectDevice();
    //Q_INVOKABLE void disconnectDevice();
};
