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

std::expected<void, ConnectionErrorCodes> ConnectionService::connect(DeviceType2 type, const std::wstring& address)
{
    auto* device = context_.device();
    if (!device) {
        return std::unexpected(ConnectionErrorCodes::DeviceNotSet);
    }

    if (!device->ensureDevice(toHardware(type))) {
        return std::unexpected(ConnectionErrorCodes::CreateDeviceFailed);
    }

    const auto connectionResult = device->connect(address);

    if (!connectionResult.has_value()) {
        const auto error = fromHardware(connectionResult.error());
        return std::unexpected(error);
    }

    return {};
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