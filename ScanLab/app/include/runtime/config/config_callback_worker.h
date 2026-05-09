#pragma once

#include "runtime/config/config_callback_service.h"

#include <QObject>
#include <QVariantMap>

class DeviceContext;

class ConfigCallbackWorker : public QObject
{
    Q_OBJECT

public:
    explicit ConfigCallbackWorker(DeviceContext& context, QObject* parent = nullptr);
    ~ConfigCallbackWorker() override;

public slots:
    void startWatching();
    void stopWatching();

signals:
    void configSnapshotUpdated(QVariantMap snapshot);

private:
    ConfigCallbackService service_;
};
