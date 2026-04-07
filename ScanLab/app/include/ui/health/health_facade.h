#pragma once

#include <QObject>
#include <QThread>

class DeviceContext;

class HealthFacade : public QObject
{
    Q_OBJECT
public:
    explicit HealthFacade(DeviceContext& context, QObject* parent = nullptr);
    ~HealthFacade() override;
private:
    QThread workerThread_;
};
