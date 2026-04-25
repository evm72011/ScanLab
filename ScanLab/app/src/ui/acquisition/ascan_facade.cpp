#include "ui/acquisition/ascan_facade.h"

#include "runtime/acquisition/ascan/ascan_worker.h"
#include "runtime/device/device_context.h"

#include "scanlab/acquisition/ascan/frame.h"

#include <QMetaType>
#include <utility>

using Frame = scanlab::acquisition::ascan::Frame;
using EnvelopePoint = scanlab::acquisition::ascan::EnvelopePoint;

AScanFacade::AScanFacade(DeviceContext& context, QObject* parent)
    : QObject(parent)
{
    qRegisterMetaType<Frame>();

    worker_ = new AScanWorker(context);
    worker_->moveToThread(&workerThread_);

    connect(
        &workerThread_,
        &QThread::finished,
        worker_,
        &QObject::deleteLater);

    connect(
        this,
        &AScanFacade::requestStart,
        worker_,
        &AScanWorker::start,
        Qt::QueuedConnection);

    connect(
        this,
        &AScanFacade::requestStop,
        worker_,
        &AScanWorker::stop,
        Qt::QueuedConnection);

    connect(
        this,
        &AScanFacade::requestSetCropMargins,
        worker_,
        &AScanWorker::setCropMargins,
        Qt::QueuedConnection);

    connect(
        worker_,
        &AScanWorker::frameUpdated,
        this,
        [this](const Frame& frame) {
            QVector<EnvelopePoint> values;
            values.reserve(static_cast<qsizetype>(frame.samples.size()));

            for (const auto&  sample : frame.samples) {
                values.push_back(sample);
            }

            setSamples(std::move(values));
            emit frameReady();
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &AScanWorker::started,
        this,
        [this]() {
            setRunning(true);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &AScanWorker::startFailed,
        this,
        [this]() {
            setRunning(false);
        },
        Qt::QueuedConnection);

    connect(
        worker_,
        &AScanWorker::stopped,
        this,
        [this](bool stillRunning) {
            setRunning(stillRunning);
        },
        Qt::QueuedConnection);

    workerThread_.start();
}

AScanFacade::~AScanFacade()
{
    emit requestStop();

    if (workerThread_.isRunning()) {
        workerThread_.quit();
        workerThread_.wait();
    }
}

bool AScanFacade::running() const
{
    return running_;
}

void AScanFacade::start()
{
    emit requestStart();
}

void AScanFacade::stop()
{
    emit requestStop();
}

void AScanFacade::setCropMargins(qreal leftFraction, qreal rightFraction)
{
    emit requestSetCropMargins(leftFraction, rightFraction);
}

QVector<EnvelopePoint> AScanFacade::samplesSnapshot() const
{
    QMutexLocker lock(&samplesMutex_);
    return samples_;
}

void AScanFacade::setSamples(QVector<EnvelopePoint> value)
{
    QMutexLocker lock(&samplesMutex_);
    samples_ = std::move(value);
}

void AScanFacade::setRunning(bool value)
{
    if (running_ == value) {
        return;
    }

    running_ = value;
    emit runningChanged();
}