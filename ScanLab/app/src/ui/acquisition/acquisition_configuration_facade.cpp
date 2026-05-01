#include "ui/acquisition/acquisition_configuration_facade.h"

#include "runtime/acquisition/acquisition_configuration_worker.h"
#include "runtime/device/device_context.h"

namespace sa = scanlab::acquisition;

AcquisitionConfigurationFacade::AcquisitionConfigurationFacade(
    DeviceContext& context,
    QObject* parent)
    : QObject(parent)
{
    qRegisterMetaType<sa::AscanParameters>(
        "scanlab::acquisition::AscanParameters");

    worker_ = new AcquisitionConfigurationWorker(context);
    worker_->moveToThread(&workerThread_);

    connect(
        &workerThread_,
        &QThread::finished,
        worker_,
        &QObject::deleteLater);

    connect(
        this,
        &AcquisitionConfigurationFacade::requestReadCycleCount,
        worker_,
        &AcquisitionConfigurationWorker::readCycleCount,
        Qt::QueuedConnection);

    connect(
        this,
        &AcquisitionConfigurationFacade::requestReadAscanParameters,
        worker_,
        &AcquisitionConfigurationWorker::readAscanParameters,
        Qt::QueuedConnection);

    connect(
        this,
        &AcquisitionConfigurationFacade::requestWriteAscanParameters,
        worker_,
        &AcquisitionConfigurationWorker::writeAscanParameters,
        Qt::QueuedConnection);

    connect(
        worker_,
        &AcquisitionConfigurationWorker::cycleCountUpdated,
        this,
        [this](int value) {
            setCycleCount(value);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &AcquisitionConfigurationWorker::ascanParametersUpdated,
        this,
        [this](sa::AscanParameters parameters) {
            setCycle(parameters.cycle);
            setStart(parameters.start);
            setRange(parameters.range);
            setPointCount(parameters.pointCount);
            setUnavailable(false);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &AcquisitionConfigurationWorker::writeCompleted,
        this,
        [this]() {
            setUnavailable(false);
            emit writeSucceeded();
            refresh();
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &AcquisitionConfigurationWorker::acquisitionConfigurationUnavailable,
        this,
        [this]() {
            setUnavailable(true);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &AcquisitionConfigurationWorker::acquisitionConfigurationErrorCode,
        this,
        [this](const QString& value) {
            setErrorCode(value);
        },
        Qt::QueuedConnection);

    workerThread_.start();
}

AcquisitionConfigurationFacade::~AcquisitionConfigurationFacade()
{
    if (workerThread_.isRunning()) {
        workerThread_.quit();
        workerThread_.wait();
    }
}

int AcquisitionConfigurationFacade::cycleCount() const
{
    return cycleCount_;
}

int AcquisitionConfigurationFacade::cycle() const
{
    return cycle_;
}

double AcquisitionConfigurationFacade::start() const
{
    return start_;
}

double AcquisitionConfigurationFacade::range() const
{
    return range_;
}

int AcquisitionConfigurationFacade::pointCount() const
{
    return pointCount_;
}

bool AcquisitionConfigurationFacade::unavailable() const
{
    return unavailable_;
}

QString AcquisitionConfigurationFacade::errorCode() const
{
    return errorCode_;
}

void AcquisitionConfigurationFacade::refresh()
{
    emit requestReadCycleCount();
    //emit requestReadAscanParameters(cycle_);
}

void AcquisitionConfigurationFacade::apply()
{
    sa::AscanParameters parameters;
    parameters.cycle = cycle_;
    parameters.start = start_;
    parameters.range = range_;
    parameters.pointCount = pointCount_;

    emit requestWriteAscanParameters(parameters);
}

void AcquisitionConfigurationFacade::setCycle(int value)
{
    if (cycle_ == value) {
        return;
    }

    cycle_ = value;
    emit cycleChanged();

    emit requestReadAscanParameters(cycle_);
}

void AcquisitionConfigurationFacade::setStart(double value)
{
    if (qFuzzyCompare(start_, value)) {
        return;
    }

    start_ = value;
    emit startChanged();
}

void AcquisitionConfigurationFacade::setRange(double value)
{
    if (qFuzzyCompare(range_, value)) {
        return;
    }

    range_ = value;
    emit rangeChanged();
}

void AcquisitionConfigurationFacade::setPointCount(int value)
{
    if (pointCount_ == value) {
        return;
    }

    pointCount_ = value;
    emit pointCountChanged();
}

void AcquisitionConfigurationFacade::setCycleCount(int value)
{
    if (cycleCount_ == value) {
        return;
    }

    cycleCount_ = value;
    emit cycleCountChanged();
}

void AcquisitionConfigurationFacade::setUnavailable(bool value)
{
    if (unavailable_ == value) {
        return;
    }

    unavailable_ = value;
    emit unavailableChanged();
}

void AcquisitionConfigurationFacade::setErrorCode(const QString& value)
{
    if (errorCode_ == value) {
        return;
    }

    errorCode_ = value;
    emit errorCodeChanged();
}
