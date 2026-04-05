#include "health_worker.h"

#include <QVariantMap>

HealthWorker::HealthWorker(QObject* parent)
    : QObject(parent)
    , timer_(new QTimer(this))
{
    timer_->setSingleShot(false);
    timer_->setInterval(intervalMs_);

    connect(timer_, &QTimer::timeout,
            this, &HealthWorker::poll);
}

void HealthWorker::setHardwareDevice(scanlab::hardware::Device* device)
{
    hardwareDevice_ = device;
    monitor_.setDevice(hardwareDevice_);
}

void HealthWorker::setIntervalMs(int value)
{
    if (value < 100) {
        value = 100;
    }

    if (intervalMs_ == value) {
        return;
    }

    intervalMs_ = value;
    timer_->setInterval(intervalMs_);
}

void HealthWorker::start()
{
    if (hardwareDevice_ == nullptr) {
        return;
    }

    if (!timer_->isActive()) {
        timer_->start();
    }

    poll();
}

void HealthWorker::stop()
{
    timer_->stop();
}

void HealthWorker::poll()
{
    if (hardwareDevice_ == nullptr) {
        return;
    }

    const auto snapshot = monitor_.readTemperatureSnapshot();
    if (!snapshot.has_value()) {
        return;
    }

    QVariantList items;
    items.reserve(static_cast<int>(snapshot->sensors.size()));

    for (const auto& sensor : snapshot->sensors) {
        QVariantMap item;
        item.insert(QStringLiteral("board"), sensor.board);
        item.insert(QStringLiteral("sensor"), sensor.sensor);
        item.insert(QStringLiteral("valueCelsius"), sensor.valueCelsius);
        items.push_back(item);

        qDebug() << "[TEMP]" << sensor.board << sensor.sensor << sensor.valueCelsius;
    }

    int maxTemperature = -1;
    if (const auto maxValue = snapshot->overallMaxCelsius(); maxValue.has_value()) {
        maxTemperature = *maxValue;
    }

    emit temperatureUpdated(maxTemperature, items);
}