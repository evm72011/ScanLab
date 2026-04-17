#include "runtime/connection/connection_service.h"
#include "runtime/device/device_context.h"
#include "runtime/device/device_type.h"
#include "runtime/device/device_type_mapper.h"

#include "scanlab/hardware/device/device.h"
#include <qcontainerfwd.h>
#include <magic_enum/magic_enum.hpp>

ConnectionService::ConnectionService(DeviceContext& context)
    : context_(context)
{
}

std::expected<ConnectionResult, ConnectionError> ConnectionService::connect(DeviceType type, const std::wstring& address)
{
    auto* device = context_.device();
    if (!device) {
        return std::unexpected(ConnectionLocalError::DeviceNotSet);
    }

    if (!device->ensureDevice(toHardware(type))) {
        return std::unexpected(ConnectionLocalError::CreateDeviceFailed);
    }

    const auto connectionResult = device->connect(address);

    if (!connectionResult.has_value()) {
        const auto error = fromHardware(connectionResult.error());
        return std::unexpected(error);
    }

    return ConnectionResult {
        .serialNumber = QString::fromStdWString(connectionResult->serialNumber)
    };
}

void ConnectionService::disconnect()
{
    auto* device = context_.device();
    if (!device) {
        return;
    }

    device->disconnect();
}

bool ConnectionService::isConnected() const
{
    auto* device = context_.device();
    return device && device->isConnected();
}