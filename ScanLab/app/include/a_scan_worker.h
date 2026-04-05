#pragma once

#include <QObject>
#include <QHash>
#include <QVector>

#include "device_facade.h"
#include "scanlab/hardware/a_scan_acquisition.h"

class AScanWorker : public QObject
{
    Q_OBJECT

public:
    explicit AScanWorker(QObject* parent = nullptr);
    ~AScanWorker() override;

public slots:
    void setDevice(DeviceFacade* device);
    void start();
    void stop();
    void setSampleCount(int value);

signals:
    void samplesReady(const QVector<float>& samples);

private:
    DeviceFacade* device_ = nullptr;
    scanlab::hardware::AScanAcquisition acquisition_;
    int sampleCount_ = 512;

    QHash<int, QVector<float>> frames_;
    int selectedCycle_ = 0;
};

/*
#pragma once

#include <QObject>
#include <QTimer>
#include <QVector>

class AScanWorker : public QObject
{
    Q_OBJECT

public:
    explicit AScanWorker(QObject* parent = nullptr);

public slots:
    void start();
    void stop();
    void setSampleCount(int value);

signals:
    void samplesReady(const QVector<float>& samples);

private slots:
    void generate();

private:
    static float pulse(float t, float center, float width, float amplitude);

private:
    QTimer* timer_ = nullptr;
    int sampleCount_ = 512;
    float phase_ = 0.0f;
};
*/