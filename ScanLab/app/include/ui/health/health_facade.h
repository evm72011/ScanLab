#pragma once

#include <QObject>
#include <QThread>

class DeviceContext;
class HealthWorker2;

class HealthFacade : public QObject
{
    Q_OBJECT
public:
    explicit HealthFacade(DeviceContext& context, QObject* parent = nullptr);
    ~HealthFacade() override;

private:
    HealthWorker2* worker_ = nullptr;
    QThread workerThread_;
};
