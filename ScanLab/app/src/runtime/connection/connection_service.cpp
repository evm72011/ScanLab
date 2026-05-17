#include "runtime/connection/connection_service.h"
#include "runtime/device/device_context.h"
#include "runtime/device/device_type.h"
#include "runtime/device/device_type_mapper.h"

#include "scanlab/device/device.h"
#include <magic_enum/magic_enum.hpp>
#include <qcontainerfwd.h>

ConnectionService::ConnectionService(DeviceContext& context)
    : context_(context)
{
}

std::expected<ConnectionResult, ConnectionError> ConnectionService::connect(DeviceType type,
    const std::wstring& address)
{
    auto* device = context_.device();
    if (!device)
    {
        return std::unexpected(ConnectionShellError::DeviceContextNotSet);
    }

    if (!device->ensureDevice(toHardware(type)))
    {
        return std::unexpected(ConnectionShellError::CreateDeviceFailed);
    }

    const auto result = device->connect(address);

    if (!result.has_value())
    {
        const auto error = fromScanlabError(result.error());
        return std::unexpected(error);
    }

    return ConnectionResult{ //
        .serialNumber = QString::fromStdWString(result->serialNumber)
    };
}

void ConnectionService::disconnect()
{
    auto* device = context_.device();
    if (!device)
    {
        return;
    }

    device->disconnect();
}

bool ConnectionService::isConnected() const
{
    auto* device = context_.device();
    return device && device->isConnected();
}