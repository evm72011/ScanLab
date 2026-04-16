#pragma once

#include <expected>
#include <string>
#include "runtime/device/device_type.h"
#include "runtime/connection/connection_error.h"
#include "runtime/connection/connection_result.h"

class DeviceContext;

class ConnectionService
{
public:
    explicit ConnectionService(DeviceContext& context);

    std::expected<ConnectionResult, ConnectionError> connect(DeviceType type, const std::wstring& address);
    void disconnect();

    bool isConnected() const;

private:
    DeviceContext& context_;
};
