#pragma once

#include <QObject>
#include <QThread>
#include <QVariantList>
#include <qqmlintegration.h>

class DeviceContext;
class AScanWorker;

class AScanFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList samples READ samples NOTIFY samplesChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)

public:
    explicit AScanFacade(DeviceContext& context, QObject* parent = nullptr);
    ~AScanFacade() override;

    QVariantList samples() const;
    bool running() const;

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

signals:
    void requestStart();
    void requestStop();

    void samplesChanged();
    void runningChanged();

private:
    void setSamples(const QVariantList& value);
    void setRunning(bool value);

private:
    QVariantList samples_;
    bool running_ = false;

    AScanWorker* worker_ = nullptr;
    QThread workerThread_;
};
