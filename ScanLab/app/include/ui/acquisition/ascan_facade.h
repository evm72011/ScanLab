#pragma once

#include <QMutex>
#include <QObject>
#include <QThread>
#include <QVector>
#include <QtTypes>
#include <qqmlintegration.h>

#include "scanlab/acquisition/ascan/envelope_point.h"

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
    void setCropMargins(qreal leftFraction, qreal rightFraction);

    Q_INVOKABLE void setCycleFilter(int cycle);
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    QVector<scanlab::acquisition::ascan::EnvelopePoint> samplesSnapshot() const;

signals:
    void requestStart();
    void requestStop();

    void frameReady();
    void runningChanged();
    void requestSetCropMargins(qreal leftFraction, qreal rightFraction);
    void requestSetCycleFilter(int cycle);

private:
    using EnvelopePoint = scanlab::acquisition::ascan::EnvelopePoint;

    void setSamples(QVector<EnvelopePoint> value);
    void setRunning(bool value);

private:
    AScanWorker* worker_ = nullptr;
    QThread workerThread_;

    mutable QMutex samplesMutex_;
    QVector<EnvelopePoint> samples_;

    bool running_ = false;
};