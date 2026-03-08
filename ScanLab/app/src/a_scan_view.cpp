#include "a_scan_view.h"
#include "a_scan_worker.h"

#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QMetaType>

AScanView::AScanView(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setAntialiasing(true);

    qRegisterMetaType<QVector<float>>("QVector<float>");

    worker_ = new AScanWorker();
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this, &AScanView::requestStart, worker_, &AScanWorker::start, Qt::QueuedConnection);
    connect(this, &AScanView::requestStop, worker_, &AScanWorker::stop, Qt::QueuedConnection);
    connect(this, &AScanView::requestSampleCount, worker_, &AScanWorker::setSampleCount, Qt::QueuedConnection);

    connect(worker_, &AScanWorker::samplesReady,
            this, &AScanView::onSamplesReady,
            Qt::QueuedConnection);

    workerThread_.start();
    emit requestSampleCount(sampleCount_);
}

AScanView::~AScanView()
{
    emit requestStop();
    workerThread_.quit();
    workerThread_.wait();
}

void AScanView::paint(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    const QRectF r = boundingRect();

    painter->fillRect(r, QColor("#1e1e1e"));

    drawGrid(*painter, r);
    drawAxes(*painter, r);
    drawSignal(*painter, r);
}

int AScanView::sampleCount() const
{
    return sampleCount_;
}

void AScanView::setSampleCount(int value)
{
    if (sampleCount_ == value || value < 2) {
        return;
    }

    sampleCount_ = value;
    emit requestSampleCount(sampleCount_);
    emit sampleCountChanged();
}

qreal AScanView::minY() const
{
    return minY_;
}

void AScanView::setMinY(qreal value)
{
    if (qFuzzyCompare(minY_, value)) {
        return;
    }

    minY_ = value;
    update();
    emit minYChanged();
}

qreal AScanView::maxY() const
{
    return maxY_;
}

void AScanView::setMaxY(qreal value)
{
    if (qFuzzyCompare(maxY_, value)) {
        return;
    }

    maxY_ = value;
    update();
    emit maxYChanged();
}

bool AScanView::active() const
{
    return active_;
}

void AScanView::setActive(bool value)
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

void AScanView::onSamplesReady(const QVector<float>& samples)
{
    {
        QMutexLocker locker(&samplesMutex_);
        samples_ = samples;
    }

    update();
}

void AScanView::drawGrid(QPainter& p, const QRectF& r)
{
    p.save();

    QPen pen(QColor(255, 255, 255, 25));
    pen.setWidth(1);
    p.setPen(pen);

    constexpr int vSteps = 10;
    constexpr int hSteps = 8;

    for (int i = 0; i <= vSteps; ++i) {
        const qreal x = r.left() + i * r.width() / vSteps;
        p.drawLine(QPointF(x, r.top()), QPointF(x, r.bottom()));
    }

    for (int i = 0; i <= hSteps; ++i) {
        const qreal y = r.top() + i * r.height() / hSteps;
        p.drawLine(QPointF(r.left(), y), QPointF(r.right(), y));
    }

    p.restore();
}

void AScanView::drawAxes(QPainter& p, const QRectF& r)
{
    p.save();

    QPen pen(QColor(255, 255, 255, 56));
    pen.setWidth(1);
    p.setPen(pen);

    const qreal zeroY = r.top() + mapY(0.0f, r.height());
    p.drawLine(QPointF(r.left(), zeroY), QPointF(r.right(), zeroY));

    p.restore();
}

void AScanView::drawSignal(QPainter& p, const QRectF& r)
{
    QVector<float> data;
    {
        QMutexLocker locker(&samplesMutex_);
        data = samples_;
    }

    if (data.size() < 2) {
        return;
    }

    QPainterPath path;
    for (int i = 0; i < data.size(); ++i) {
        const qreal x = r.left() + i * (r.width() / (data.size() - 1));
        const qreal y = r.top() + mapY(data[i], r.height());

        if (i == 0) {
            path.moveTo(x, y);
        } else {
            path.lineTo(x, y);
        }
    }

    p.save();

    QPen pen(QColor("#6aa9ff"));
    pen.setWidthF(1.5);
    p.setPen(pen);
    p.drawPath(path);

    p.restore();
}

qreal AScanView::mapY(float v, qreal h) const
{
    const qreal t = (v - minY_) / (maxY_ - minY_);
    return h * (1.0 - t);
}
