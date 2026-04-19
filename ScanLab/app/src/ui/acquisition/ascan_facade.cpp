#include "ui/acquisition/ascan_facade.h"

#include "runtime/acquisition/ascan/ascan_worker.h"
#include "runtime/device/device_context.h"

#include "scanlab/acquisition/ascan/a_scan_frame.h"

#include <QMetaType>

AScanFacade::AScanFacade(DeviceContext& context, QObject* parent)
    : QObject(parent)
{
    qRegisterMetaType<scanlab::acquisition::AScanFrame>("scanlab::hardware::AScanFrame");

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
        worker_,
        &AScanWorker::frameUpdated,
        this,
        [this](const scanlab::acquisition::AScanFrame& frame) {
            QVariantList values;
            values.reserve(static_cast<qsizetype>(frame.samples.size()));

            for (float sample : frame.samples) {
                values.push_back(sample);
            }

            setSamples(values);
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

QVariantList AScanFacade::samples() const
{
    return samples_;
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

void AScanFacade::setSamples(const QVariantList& value)
{
    samples_ = value;
    emit samplesChanged();
}

void AScanFacade::setRunning(bool value)
{
    if (running_ == value) {
        return;
    }

    running_ = value;
    emit runningChanged();
}