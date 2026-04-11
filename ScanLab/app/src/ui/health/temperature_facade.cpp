#include "ui/health/temperature_facade.h"

#include "runtime/device/device_context.h"
#include "runtime/health/health_worker.h"

#include <QDebug>
#include <QVariantMap>

TemperatureFacade::TemperatureFacade(DeviceContext& context, QObject* parent)
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
        &TemperatureFacade::requestPollMaxTemperature,
        worker_,
        &HealthWorker2::pollMaxTemperature,
        Qt::QueuedConnection);

    connect(
        &timer_,
        &QTimer::timeout,
        this,
        &TemperatureFacade::pollMaxTemperature);

    connect(
        worker_,
        &HealthWorker2::maxTemperatureUpdated,
        this,
        [this](int value) {
            setMaxTemperature(value);
            setMaxTemperatureUnavailable(false);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &HealthWorker2::maxTemperatureUnavailable,
        this,
        [this]() {
            setMaxTemperatureUnavailable(true);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &HealthWorker2::maxTemperatureErrorCode,
        this,
        [this](QString value) {
            setMaxTemperatureErrorCode(value);
        },
        Qt::QueuedConnection);

    timer_.setSingleShot(false);

    workerThread_.start();
}

TemperatureFacade::~TemperatureFacade()
{
    timer_.stop();

    if (workerThread_.isRunning()) {
        workerThread_.quit();
        workerThread_.wait();
    }
}

bool TemperatureFacade::maxTemperatureUnavailable() const
{
    return maxTemperatureUnavailable_;
}

int TemperatureFacade::maxTemperature() const
{
    return maxTemperature_;
}

QString TemperatureFacade::maxTemperatureErrorCode() const
{
    return maxTemperatureErrorCode_;
}

void TemperatureFacade::startMaxTemperaturePolling()
{
    if (timer_.isActive()) {
        return;
    }

    timer_.setInterval(interval_);
    timer_.start();

    pollMaxTemperature();
}

void TemperatureFacade::stopMaxTemperaturePolling()
{
    if (!timer_.isActive()) {
        return;
    }

    timer_.stop();
}

void TemperatureFacade::pollMaxTemperature()
{
    emit requestPollMaxTemperature();
}

void TemperatureFacade::setMaxTemperature(int value)
{
    if (maxTemperature_ == value) {
        return;
    }
    maxTemperature_ = value;
    emit maxTemperatureChanged();
}

void TemperatureFacade::setMaxTemperatureUnavailable(bool value)
{
    if (maxTemperatureUnavailable_ == value) {
        return;
    }

    maxTemperatureUnavailable_ = value;
    emit maxTemperatureUnavailableChanged();
}

void TemperatureFacade::setMaxTemperatureErrorCode(const QString& value)
{
    if (maxTemperatureErrorCode_ == value) {
        return;
    }

    maxTemperatureErrorCode_ = value;
    emit maxTemperatureErrorCodeChanged();
}