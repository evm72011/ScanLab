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
    auto emitResult = [this](scanlab::hardware::ConnectResult result, bool isConnected)
    {
        const auto statusCode =
            QString::fromUtf8(magic_enum::enum_name(result).data());

        emit connectCompleted(
            static_cast<int>(result),
            isConnected,
            statusCode);
    };

    if (hardwareDevice_ == nullptr) {
        emitResult(scanlab::hardware::ConnectResult::DeviceNotSet, false);
        return;
    }

    hardwareDevice_->resetDevice();
    if (!hardwareDevice_->setDevice(toHardware(type))) {
        emitResult(scanlab::hardware::ConnectResult::DeviceNotSet, false);
        return;
    }

    const auto result = hardwareDevice_->connect(address.toStdWString());
    emitResult(result, hardwareDevice_->isConnected());
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