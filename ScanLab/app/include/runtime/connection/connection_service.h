#pragma once

#include "runtime/device/device_type.h"
#include "runtime/connection/connection_result.h"

class DeviceContext;

class ConnectionService
{
public:
    explicit ConnectionService(DeviceContext& context);

    ConnectionResult connect(DeviceType2 type, const std::wstring& address);
    void disconnect();

    bool isConnected() const;

private:
    DeviceContext& context_;
};
