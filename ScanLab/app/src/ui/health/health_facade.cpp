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
        &HealthFacade::requestPollMaxTemperature,
        worker_,
        &HealthWorker2::pollMaxTemperature,
        Qt::QueuedConnection);

    connect(
        &timer_,
        &QTimer::timeout,
        this,
        &HealthFacade::pollMaxTemperature);

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

HealthFacade::~HealthFacade()
{
    timer_.stop();

    if (workerThread_.isRunning()) {
        workerThread_.quit();
        workerThread_.wait();
    }
}

bool HealthFacade::maxTemperatureUnavailable() const
{
    return maxTemperatureUnavailable_;
}

int HealthFacade::maxTemperature() const
{
    return maxTemperature_;
}

QString HealthFacade::maxTemperatureErrorCode() const
{
    return maxTemperatureErrorCode_;
}

void HealthFacade::startMaxTemperaturePolling()
{
    if (timer_.isActive()) {
        return;
    }

    timer_.setInterval(interval_);
    timer_.start();

    pollMaxTemperature();
}

void HealthFacade::stopMaxTemperaturePolling()
{
    if (!timer_.isActive()) {
        return;
    }

    timer_.stop();
}

void HealthFacade::pollMaxTemperature()
{
    emit requestPollMaxTemperature();
}

void HealthFacade::setMaxTemperature(int value)
{
    if (maxTemperature_ == value) {
        return;
    }
    maxTemperature_ = value;
    emit maxTemperatureChanged();
}

void HealthFacade::setMaxTemperatureUnavailable(bool value)
{
    if (maxTemperatureUnavailable_ == value) {
        return;
    }

    maxTemperatureUnavailable_ = value;
    emit maxTemperatureUnavailableChanged();
}

void HealthFacade::setMaxTemperatureErrorCode(const QString& value)
{
    if (maxTemperatureErrorCode_ == value) {
        return;
    }

    maxTemperatureErrorCode_ = value;
    emit maxTemperatureErrorCodeChanged();
}