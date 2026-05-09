#include "b_scan_view.h"
#include "b_scan_worker.h"

#include <QMutexLocker>

BScanView::BScanView(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setRenderTarget(QQuickPaintedItem::Image);

    worker_ = new BScanWorker();
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this, &BScanView::requestStart, worker_, &BScanWorker::start, Qt::QueuedConnection);
    connect(this, &BScanView::requestStop, worker_, &BScanWorker::stop, Qt::QueuedConnection);
    connect(this, &BScanView::requestResize, worker_, &BScanWorker::setSize, Qt::QueuedConnection);

    connect(worker_,
        &BScanWorker::frameReady,
        this,
        &BScanView::onFrameReady,
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

BScanView::~BScanView()
{
    emit requestStop();
    workerThread_.quit();
    workerThread_.wait();
}

bool BScanView::active() const
{
    return active_;
}

void BScanView::setActive(bool value)
{
    if (active_ == value)
    {
        return;
    }

    active_ = value;

    if (active_)
    {
        emit requestStart();
    }
    else
    {
        emit requestStop();
    }

    emit activeChanged();
}

void BScanView::onFrameReady(const QImage& image)
{
    {
        QMutexLocker locker(&imageMutex_);
        image_ = image.copy();
    }

    update();
}

void BScanView::paint(QPainter* painter)
{
    QImage imageCopy;

    {
        QMutexLocker locker(&imageMutex_);
        imageCopy = image_;
    }

    if (imageCopy.isNull())
    {
        return;
    }

    painter->drawImage(boundingRect(), imageCopy);
}
