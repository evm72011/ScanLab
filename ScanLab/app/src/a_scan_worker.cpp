#include "a_scan_worker.h"

#include <QMetaObject>
#include <utility>

AScanWorker::AScanWorker(QObject* parent)
    : QObject(parent)
{
    /*
    acquisition_.setSamplesHandler(
        [this](scanlab::hardware::AScanAcquisition::Frame frame)
        {
            QVector<float> qSamples;
            qSamples.reserve(static_cast<qsizetype>(frame.samples.size()));

            for (float v : frame.samples) {
                qSamples.push_back(v);
            }

            QMetaObject::invokeMethod(
                this,
                [this, cycle = frame.cycle, qSamples = std::move(qSamples)]() mutable
                {
                    frames_[cycle] = qSamples;

                    if (!frames_.contains(selectedCycle_)) {
                        selectedCycle_ = cycle;
                    }

                    const auto it = frames_.find(selectedCycle_);
                    if (it != frames_.end()) {
                        emit samplesReady(it.value());
                    }
                },
                Qt::QueuedConnection);
        });
*/
}

AScanWorker::~AScanWorker()
{
    /*
    acquisition_.stop();
    updatePulsing(false);
*/
}
/*
void AScanWorker::setDevice(DeviceFacade* device)
{
    acquisition_.stop();
    device_ = device;
    frames_.clear();
    updatePulsing(false);
}

void AScanWorker::start()
{
    if (device_ == nullptr) {
        return;
    }

    auto* hardwareDevice = device_->hardwareDevice();
    if (hardwareDevice == nullptr) {
        return;
    }

    acquisition_.setDevice(hardwareDevice);
    acquisition_.setTargetSampleCount(sampleCount_);
    acquisition_.start();
    updatePulsing(true);
}

void AScanWorker::stop()
{
    acquisition_.stop();
    updatePulsing(false);
}

void AScanWorker::setSampleCount(int value)
{
    if (value < 2) {
        return;
    }

    sampleCount_ = value;
    acquisition_.setTargetSampleCount(sampleCount_);
}

void AScanWorker::updatePulsing(bool value)
{
    if (!device_) {
        return;
    }

    QMetaObject::invokeMethod(
        device_,
        [facade = device_, value]() {
            if (facade) {
                facade->setPulsing(value);
            }
        },
        Qt::QueuedConnection);
}
*/