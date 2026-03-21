#include "c_scan_view.h"
#include "c_scan_worker.h"

#include <QMutexLocker>
#include <QPainter>

CScanView::CScanView(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setRenderTarget(QQuickPaintedItem::Image);

    worker_ = new CScanWorker();
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this, &CScanView::requestStart, worker_, &CScanWorker::start, Qt::QueuedConnection);
    connect(this, &CScanView::requestStop, worker_, &CScanWorker::stop, Qt::QueuedConnection);
    connect(this, &CScanView::requestResize, worker_, &CScanWorker::setSize, Qt::QueuedConnection);

    connect(worker_, &CScanWorker::frameReady,
            this, &CScanView::onFrameReady,
            Qt::QueuedConnection);

    connect(this, &QQuickItem::widthChanged, this, [this]() {
        emit requestResize(static_cast<int>(width()), static_cast<int>(height()));
    });

    connect(this, &QQuickItem::heightChanged, this, [this]() {
        emit requestResize(static_cast<int>(width()), static_cast<int>(height()));
    });

    workerThread_.start();
    emit requestResize(static_cast<int>(width()), static_cast<int>(height()));
}

CScanView::~CScanView()
{
    emit requestStop();
    workerThread_.quit();
    workerThread_.wait();
}

bool CScanView::active() const
{
    return active_;
}

void CScanView::setActive(bool value)
{
    if (active_ == value) {
        return;
    }

    active_ = value;

    if (active_) {
        emit requestStart();
    } else {
        emit requestStop();
    }

    emit activeChanged();
}

void CScanView::onFrameReady(const QImage& image)
{
    {
        QMutexLocker locker(&imageMutex_);
        image_ = image.copy();
    }

    update();
}

void CScanView::paint(QPainter* painter)
{
    QImage imageCopy;

    {
        QMutexLocker locker(&imageMutex_);
        imageCopy = image_;
    }

    if (imageCopy.isNull()) {
        return;
    }

    painter->drawImage(boundingRect(), imageCopy);
}
