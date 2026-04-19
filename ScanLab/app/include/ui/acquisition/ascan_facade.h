#pragma once

#include <QMutex>
#include <QObject>
#include <QThread>
#include <QVector>
#include <qqmlintegration.h>

class DeviceContext;
class AScanWorker;

class AScanFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running NOTIFY runningChanged)

public:
    explicit AScanFacade(DeviceContext& context, QObject* parent = nullptr);
    ~AScanFacade() override;

    bool running() const;

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    QVector<float> samplesSnapshot() const;

signals:
    void requestStart();
    void requestStop();

    void frameReady();
    void runningChanged();

private:
    void setSamples(QVector<float> value);
    void setRunning(bool value);

private:
    AScanWorker* worker_ = nullptr;
    QThread workerThread_;

    mutable QMutex samplesMutex_;
    QVector<float> samples_;

    bool running_ = false;
};