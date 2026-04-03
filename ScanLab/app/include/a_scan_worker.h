#pragma once

#include <QObject>
#include <QVector>

namespace scanlab::hardware {
class Device;
class AScanAcquisition;
} // namespace scanlab::hardware

class AScanWorker : public QObject
{
    Q_OBJECT

public:
    explicit AScanWorker(QObject* parent = nullptr);
    ~AScanWorker() override;

public slots:
    void setDevice(scanlab::hardware::Device* device);
    void start();
    void stop();
    void setSampleCount(int value);

signals:
    void samplesReady(const QVector<float>& samples);

private:
    class Impl;
    Impl* impl_;
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