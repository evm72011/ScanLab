#include "ui/health/health_facade.h"

#include "runtime/device/device_context.h"
#include "runtime/health/health_worker.h"

#include <QDebug>
#include <QVariantMap>

HealthFacade::HealthFacade(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , timer_(this)
{
    worker_ = new HealthWorker2(context);
    worker_->moveToThread(&workerThread_);

    connect(
        &workerThread_,
        &QThread::finished,
        worker_,
        &QObject::deleteLater);

    connect(
        this,
        &HealthFacade::requestPoll,
        worker_,
        &HealthWorker2::poll,
        Qt::QueuedConnection);

    connect(
        &timer_,
        &QTimer::timeout,
        this,
        &HealthFacade::poll);

    connect(
        worker_,
        &HealthWorker2::temperatureUpdated,
        this,
        [this](scanlab::hardware::TemperatureSnapshot snapshot) {
            qDebug() << "HealthFacade: temperature updated";
            setTemperatureSnapshot(std::move(snapshot));
            setTemperatureUnavailable(false);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &HealthWorker2::temperatureUnavailable,
        this,
        [this]() {
            qDebug() << "HealthFacade: temperature unavailable";
            setTemperatureUnavailable(true);
        },
        Qt::QueuedConnection);

    timer_.setSingleShot(false);

    workerThread_.start();
}

HealthFacade::~HealthFacade()
{
    timer_.stop();

    if (workerThread_.isRunning()) {
        workerThread_.quit();
        workerThread_.wait();
    }
}

bool HealthFacade::temperatureUnavailable() const
{
    return temperatureUnavailable_;
}

int HealthFacade::maxTemperature() const
{
    const auto overall = temperatureSnapshot_.overallMaxCelsius();
    return overall.has_value() ? *overall : -1;
}

bool HealthFacade::hasTemperature() const
{
    return !temperatureUnavailable_
           && !temperatureSnapshot_.sensors.empty()
           && maxTemperature() >= 0;
}

QVariantList HealthFacade::temperatures() const
{
    QVariantList result;
    result.reserve(static_cast<qsizetype>(temperatureSnapshot_.sensors.size()));

    for (const auto& sensor : temperatureSnapshot_.sensors) {
        QVariantMap item;
        item.insert("board", sensor.board);
        item.insert("sensor", sensor.sensor);
        item.insert("valueCelsius", sensor.valueCelsius);
        result.push_back(item);
    }

    return result;
}

void HealthFacade::startPolling()
{
    if (timer_.isActive()) {
        return;
    }

    timer_.setInterval(interval_);
    timer_.start();

    poll();
}

void HealthFacade::stopPolling()
{
    if (!timer_.isActive()) {
        return;
    }

    timer_.stop();
}

void HealthFacade::poll()
{
    emit requestPoll();
}

void HealthFacade::setTemperatureSnapshot(scanlab::hardware::TemperatureSnapshot value)
{
    temperatureSnapshot_ = std::move(value);
    emit temperatureSnapshotChanged();
}

void HealthFacade::setTemperatureUnavailable(bool value)
{
    if (temperatureUnavailable_ == value) {
        return;
    }

    temperatureUnavailable_ = value;
    emit temperatureUnavailableChanged();
}