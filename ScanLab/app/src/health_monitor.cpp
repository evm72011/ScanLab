#include "health_monitor.h"

#include "health_worker.h"

#include <QMetaObject>

HealthMonitor::HealthMonitor(QObject* parent)
    : QObject(parent)
{
    worker_ = new HealthWorker();
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished,
            worker_, &QObject::deleteLater);

    connect(worker_, &HealthWorker::temperatureUpdated,
            this,
            [this](int maxTemperature, const QVariantList& temperatures) {
                maxTemperature_ = maxTemperature;
                temperatures_ = temperatures;
                emit temperatureChanged();
            },
            Qt::QueuedConnection);

    workerThread_.start();

    QMetaObject::invokeMethod(
        worker_,
        [this]() {
            if (worker_ != nullptr) {
                worker_->setIntervalMs(intervalMs_);
            }
        },
        Qt::QueuedConnection);
}

HealthMonitor::~HealthMonitor()
{
    if (worker_ != nullptr && workerThread_.isRunning()) {
        QMetaObject::invokeMethod(
            worker_,
            [this]() {
                if (worker_ != nullptr) {
                    worker_->stop();
                    worker_->setHardwareDevice(nullptr);
                }
            },
            Qt::BlockingQueuedConnection);
    }

    workerThread_.quit();
    workerThread_.wait();
}

DeviceFacade* HealthMonitor::device() const
{
    return device_;
}

void HealthMonitor::setDevice(DeviceFacade* value)
{
    if (device_ == value) {
        return;
    }

    if (device_ != nullptr) {
        disconnect(device_, nullptr, this, nullptr);
    }

    device_ = value;
    clearTemperatureState();

    if (device_ != nullptr) {
        connect(device_, &DeviceFacade::connectionStateChanged,
                this,
                [this]() {
                    syncWorkerState();
                });

        syncWorkerState();
    } else {
        if (worker_ != nullptr) {
            QMetaObject::invokeMethod(
                worker_,
                [this]() {
                    if (worker_ != nullptr) {
                        worker_->stop();
                        worker_->setHardwareDevice(nullptr);
                    }
                },
                Qt::QueuedConnection);
        }
    }

    emit deviceChanged();
}

bool HealthMonitor::hasTemperature() const
{
    return maxTemperature_ >= 0 || !temperatures_.isEmpty();
}

int HealthMonitor::maxTemperature() const
{
    return maxTemperature_;
}

QVariantList HealthMonitor::temperatures() const
{
    return temperatures_;
}

int HealthMonitor::intervalMs() const
{
    return intervalMs_;
}

void HealthMonitor::setIntervalMs(int value)
{
    if (value < 100) {
        value = 100;
    }

    if (intervalMs_ == value) {
        return;
    }

    intervalMs_ = value;
    emit intervalMsChanged();

    if (worker_ != nullptr) {
        QMetaObject::invokeMethod(
            worker_,
            [this, value]() {
                if (worker_ != nullptr) {
                    worker_->setIntervalMs(value);
                }
            },
            Qt::QueuedConnection);
    }
}

void HealthMonitor::clearTemperatureState()
{
    maxTemperature_ = -1;
    temperatures_.clear();
    emit temperatureChanged();
}

void HealthMonitor::syncWorkerState()
{
    if (worker_ == nullptr) {
        return;
    }

    if (device_ == nullptr ||
        device_->connectionState() != ConnectionState::Connected) {
        QMetaObject::invokeMethod(
            worker_,
            [this]() {
                if (worker_ != nullptr) {
                    worker_->stop();
                    worker_->setHardwareDevice(nullptr);
                }
            },
            Qt::QueuedConnection);

        clearTemperatureState();
        return;
    }

    auto* hardwareDevice = device_->hardwareDevice();

    QMetaObject::invokeMethod(
        worker_,
        [this, hardwareDevice]() {
            if (worker_ != nullptr) {
                worker_->setIntervalMs(intervalMs_);
                worker_->setHardwareDevice(hardwareDevice);
                worker_->start();
            }
        },
        Qt::QueuedConnection);
}