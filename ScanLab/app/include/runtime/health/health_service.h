#pragma once

class DeviceContext;

class HealthService
{
public:
    explicit HealthService(DeviceContext& context);

private:
    DeviceContext& context_;
};
