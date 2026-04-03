#pragma once

#include <QObject>
#include <QString>

#include "device_type_mapper.h"
#include "scanlab/hardware/device.h"
#include <magic_enum/magic_enum.hpp>

class DeviceWorker : public QObject
{
    Q_OBJECT

public:
    explicit DeviceWorker(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

public slots:
    void resetDevice()
    {
        hw_.resetDevice();
    }

    void connectDevice(DeviceType::Type type, const QString& address)
    {
        if (!hw_.hasDevice()) {
            hw_.setDevice(toHardware(type));
        }
        const auto result = hw_.connect(address.toStdWString());

        const QString statusCode =
            QString::fromUtf8(magic_enum::enum_name(result).data());

        emit connectCompleted(
            static_cast<int>(result),
            hw_.isConnected(),
            statusCode);
    }

    void disconnectDevice()
    {
        hw_.disconnect();
        emit disconnected(hw_.isConnected());
    }

signals:
    void connectCompleted(int result, bool connected, QString statusCode);
    void disconnected(bool stillConnected);

private:
    scanlab::hardware::Device hw_;
};
