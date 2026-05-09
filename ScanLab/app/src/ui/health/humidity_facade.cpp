#include "ui/health/humidity_facade.h"

#include "runtime/device/device_context.h"
#include "runtime/health/humidity_worker.h"

#include <QDebug>
#include <QVariantMap>

HumidityFacade::HumidityFacade(DeviceContext& context, QObject* parent)
    : QObject(parent)
    , timer_(this)
{
    worker_ = new HumidityWorker(context);
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this,
        &HumidityFacade::requestPollMaxHumidity,
        worker_,
        &HumidityWorker::pollMaxHumidity,
        Qt::QueuedConnection);

    connect(&timer_, &QTimer::timeout, this, &HumidityFacade::pollMaxHumidity);

    connect(
        worker_,
        &HumidityWorker::maxHumidityUpdated,
        this,
        [this](int value) {
            setMaxHumidity(value);
            setMaxHumidityUnavailable(false);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &HumidityWorker::maxHumidityUnavailable,
        this,
        [this]() { setMaxHumidityUnavailable(true); },
        Qt::QueuedConnection);

    connect(
        worker_,
        &HumidityWorker::maxHumidityErrorCode,
        this,
        [this](QString value) { setMaxHumidityErrorCode(value); },
        Qt::QueuedConnection);

    timer_.setSingleShot(false);

    workerThread_.start();
}

HumidityFacade::~HumidityFacade()
{
    timer_.stop();

    if (workerThread_.isRunning())
    {
        workerThread_.quit();
        workerThread_.wait();
    }
}

bool HumidityFacade::maxHumidityUnavailable() const
{
    return maxHumidityUnavailable_;
}

int HumidityFacade::maxHumidity() const
{
    return maxHumidity_;
}

QString HumidityFacade::maxHumidityErrorCode() const
{
    return maxHumidityErrorCode_;
}

void HumidityFacade::startMaxHumidityPolling()
{
    if (timer_.isActive())
    {
        return;
    }

    timer_.setInterval(interval_);
    timer_.start();

    pollMaxHumidity();
}

void HumidityFacade::stopMaxHumidityPolling()
{
    if (!timer_.isActive())
    {
        return;
    }

    timer_.stop();
}

void HumidityFacade::pollMaxHumidity()
{
    emit requestPollMaxHumidity();
}

void HumidityFacade::setMaxHumidity(int value)
{
    if (maxHumidity_ == value)
    {
        return;
    }
    maxHumidity_ = value;
    emit maxHumidityChanged();
}

void HumidityFacade::setMaxHumidityUnavailable(bool value)
{
    if (maxHumidityUnavailable_ == value)
    {
        return;
    }

    maxHumidityUnavailable_ = value;
    emit maxHumidityUnavailableChanged();
}

void HumidityFacade::setMaxHumidityErrorCode(const QString& value)
{
    if (maxHumidityErrorCode_ == value)
    {
        return;
    }

    maxHumidityErrorCode_ = value;
    emit maxHumidityErrorCodeChanged();
}