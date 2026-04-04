#include "connection_worker.h"

#include "device_type_mapper.h"
#include "scanlab/hardware/connect_result.h"
#include "scanlab/hardware/device.h"

#include <magic_enum/magic_enum.hpp>

ConnectionWorker::ConnectionWorker(scanlab::hardware::Device* hardwareDevice, QObject* parent)
    : QObject(parent)
    , hardwareDevice_(hardwareDevice)
{
}

void ConnectionWorker::connectDevice(DeviceType::Type type, const QString& address)
{
    if (hardwareDevice_ == nullptr) {
        emit connectCompleted(
            static_cast<int>(scanlab::hardware::ConnectResult::DeviceNotSet),
            false,
            QStringLiteral("DeviceNotSet"));
        return;
    }

    hardwareDevice_->resetDevice();

    if (!hardwareDevice_->setDevice(toHardware(type))) {
        emit connectCompleted(
            static_cast<int>(scanlab::hardware::ConnectResult::DeviceNotSet),
            false,
            QStringLiteral("DeviceNotSet"));
        return;
    }

    const auto result = hardwareDevice_->connect(address.toStdWString());

    const QString statusCode =
        QString::fromUtf8(magic_enum::enum_name(result).data());

    emit connectCompleted(
        static_cast<int>(result),
        hardwareDevice_->isConnected(),
        statusCode);
}

void ConnectionWorker::disconnectDevice()
{
    if (hardwareDevice_ == nullptr) {
        emit disconnected(false);
        return;
    }

    hardwareDevice_->disconnect();
    emit disconnected(hardwareDevice_->isConnected());
}

void ConnectionWorker::resetDevice()
{
    if (hardwareDevice_ != nullptr) {
        hardwareDevice_->resetDevice();
    }

    emit resetCompleted();
}