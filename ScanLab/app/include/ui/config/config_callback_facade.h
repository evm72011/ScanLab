#pragma once

#include <QObject>
#include <QThread>
#include <QVariantMap>

class DeviceContext;
class ConfigCallbackWorker;

class ConfigCallbackFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantMap configSnapshot READ configSnapshot NOTIFY configSnapshotChanged)

public:
    explicit ConfigCallbackFacade(DeviceContext& context, QObject* parent = nullptr);
    ~ConfigCallbackFacade() override;

    QVariantMap configSnapshot() const;

    Q_INVOKABLE void startWatching();
    Q_INVOKABLE void stopWatching();

signals:
    void configSnapshotChanged();

signals:
    void requestStartWatching();
    void requestStopWatching();

private:
    void setConfigSnapshot(const QVariantMap& value);

    QThread workerThread_;
    ConfigCallbackWorker* worker_ = nullptr;

    QVariantMap configSnapshot_;
};
