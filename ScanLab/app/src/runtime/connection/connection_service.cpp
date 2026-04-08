#include "runtime/connection/connection_service.h"
#include "runtime/device/device_context.h"
#include "runtime/device/device_type.h"
#include "runtime/device/device_type_mapper.h"

#include "scanlab/hardware/device.h"
#include <qcontainerfwd.h>
#include <magic_enum/magic_enum.hpp>

ConnectionService::ConnectionService(DeviceContext& context)
    : context_(context)
{
}

ConnectionResult ConnectionService::connect(DeviceType2 type, const std::wstring& address)
{
    auto* device = context_.device();
    if (!device) {
        return {false, "DeviceNotSet"};
    }

    if (!device->ensureDevice(toHardware(type))) {
        return {false, "DeviceCreateFailed"};
    }

    const auto result = device->connect(address);

    return {
        device->isConnected(),
        std::string(magic_enum::enum_name(result))
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