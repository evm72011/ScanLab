#pragma once
/*
#include <QObject>
#include <QHash>
#include <QVector>

//#include "scanlab/a_scan_acquisition.h"

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
    void updatePulsing(bool value);

private:
    DeviceFacade* device_ = nullptr;
    scanlab::hardware::AScanAcquisition acquisition_;
    int sampleCount_ = 512;

    QHash<int, QVector<float>> frames_;
    int selectedCycle_ = 0;

};
*/