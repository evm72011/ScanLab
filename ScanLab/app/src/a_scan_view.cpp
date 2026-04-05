#include "a_scan_view.h"
#include "a_scan_worker.h"

#include <QHoverEvent>
#include <QMetaObject>
#include <QMutexLocker>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

#include <algorithm>

namespace
{
constexpr qreal L = 8.0;
constexpr qreal R = 8.0;
constexpr qreal T = 8.0;
constexpr qreal B_NO_LABEL = 8.0;
constexpr qreal B_LABEL = 28.0;

constexpr int H_GRID = 8;

const QColor GRID(255, 255, 255, 25);
const QColor AXIS(255, 255, 255, 56);
const QColor SIGNAL_COLOR(0x6a, 0xa9, 0xff);
const QColor TEXT_COLOR(0xa0, 0xa0, 0xa0);
const QColor CURSOR_LINE(255, 210, 80, 180);
const QColor CURSOR_TEXT_BG(20, 20, 20, 210);
const QColor CURSOR_TEXT_FG(255, 240, 190);

constexpr qreal SIGNAL_W = 3.0;
constexpr qreal CURSOR_W = 1.0;
}

AScanView::AScanView(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::NoButton);

    worker_ = new AScanWorker();
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this, &AScanView::requestStart, worker_, &AScanWorker::start);
    connect(this, &AScanView::requestStop, worker_, &AScanWorker::stop);
    connect(this, &AScanView::requestSampleCount, worker_, &AScanWorker::setSampleCount);

    connect(worker_, &AScanWorker::samplesReady,
            this, &AScanView::onSamplesReady);

    workerThread_.start();
    emit requestSampleCount(sampleCount_);
}

AScanView::~AScanView()
{
    emit requestStop();
    workerThread_.quit();
    workerThread_.wait();
}

DeviceController* AScanView::device() const
{
    return device_;
}

void AScanView::setDevice(DeviceController* v)
{
    if (device_ == v) {
        return;
    }

    if (active_) {
        emit requestStop();
    }

    device_ = v;

    QMetaObject::invokeMethod(worker_,
                              [=, this]() {
                                  worker_->setDevice(v);
                                  if (active_) {
                                      worker_->start();
                                  }
                              });

    update();
    emit deviceChanged();
}

int AScanView::sampleCount() const
{
    return sampleCount_;
}

void AScanView::setSampleCount(int v)
{
    if (v < 2 || v == sampleCount_) {
        return;
    }

    sampleCount_ = v;
    emit requestSampleCount(v);
    update();
    emit sampleCountChanged();
}

qreal AScanView::minY() const
{
    return minY_;
}

void AScanView::setMinY(qreal v)
{
    if (qFuzzyCompare(minY_, v)) {
        return;
    }

    minY_ = v;
    update();
    emit minYChanged();
}

qreal AScanView::maxY() const
{
    return maxY_;
}

void AScanView::setMaxY(qreal v)
{
    if (qFuzzyCompare(maxY_, v)) {
        return;
    }

    maxY_ = v;
    update();
    emit maxYChanged();
}

bool AScanView::active() const
{
    return active_;
}

void AScanView::setActive(bool v)
{
    if (v == active_) {
        return;
    }

    active_ = v;

    if (v) {
        emit requestStart();
    } else {
        emit requestStop();
    }

    emit activeChanged();
}

qreal AScanView::soundVelocity() const
{
    return soundVelocity_;
}

void AScanView::setSoundVelocity(qreal v)
{
    v = std::max<qreal>(0.0, v);

    if (qFuzzyCompare(v, soundVelocity_)) {
        return;
    }

    soundVelocity_ = v;
    update();
    emit soundVelocityChanged();
}

qreal AScanView::timeRangeUs() const
{
    return timeRangeUs_;
}

void AScanView::setTimeRangeUs(qreal v)
{
    v = std::max<qreal>(0.0, v);

    if (qFuzzyCompare(v, timeRangeUs_)) {
        return;
    }

    timeRangeUs_ = v;
    update();
    emit timeRangeUsChanged();
}

qreal AScanView::timeStartUs() const
{
    return timeStartUs_;
}

void AScanView::setTimeStartUs(qreal v)
{
    if (qFuzzyCompare(v, timeStartUs_)) {
        return;
    }

    timeStartUs_ = v;
    update();
    emit timeStartUsChanged();
}

int AScanView::xDivisions() const
{
    return xDivisions_;
}

void AScanView::setXDivisions(int v)
{
    v = std::max(1, v);

    if (v == xDivisions_) {
        return;
    }

    xDivisions_ = v;
    update();
    emit xDivisionsChanged();
}

void AScanView::onSamplesReady(const QVector<float>& s)
{
    QMutexLocker l(&samplesMutex_);
    samples_ = s;
    update();
}

void AScanView::hoverMoveEvent(QHoverEvent* event)
{
    const QRectF r = plotRect();
    if (r.width() <= 0.0 || r.height() <= 0.0) {
        cursorVisible_ = false;
        update();
        QQuickPaintedItem::hoverMoveEvent(event);
        return;
    }

    const qreal x = event->position().x();
    const qreal y = event->position().y();

    if (r.contains(QPointF(x, y))) {
        cursorVisible_ = true;
        cursorX_ = std::clamp<qreal>(x, r.left(), r.right());
    } else {
        cursorVisible_ = false;
    }

    update();
    QQuickPaintedItem::hoverMoveEvent(event);
}

void AScanView::hoverLeaveEvent(QHoverEvent* event)
{
    cursorVisible_ = false;
    update();
    QQuickPaintedItem::hoverLeaveEvent(event);
}

bool AScanView::hasPhysicalScale() const
{
    return soundVelocity_ > 0.0 && timeRangeUs_ > 0.0;
}

qreal AScanView::relativeToThicknessMm(qreal t) const
{
    const qreal timeUs = timeStartUs_ + t * timeRangeUs_;
    const qreal timeSec = timeUs * 1e-6;
    const qreal meters = soundVelocity_ * timeSec * 0.5;
    return meters * 1000.0;
}

QRectF AScanView::plotRect() const
{
    const qreal bottom = hasPhysicalScale() ? B_LABEL : B_NO_LABEL;
    return QRectF(L, T, width() - L - R, height() - T - bottom);
}

qreal AScanView::mapY(float v, const QRectF& r) const
{
    const qreal denom = maxY_ - minY_;
    if (qFuzzyIsNull(denom)) {
        return r.center().y();
    }

    const qreal t = (std::clamp<qreal>(v, minY_, maxY_) - minY_) / denom;
    return r.top() + r.height() * (1.0 - t);
}

qreal AScanView::mapX(qreal t, const QRectF& r) const
{
    return r.left() + r.width() * t;
}

qreal AScanView::cursorRelativeX(const QRectF& r) const
{
    if (r.width() <= 0.0) {
        return 0.0;
    }

    return std::clamp<qreal>((cursorX_ - r.left()) / r.width(), 0.0, 1.0);
}

QString AScanView::cursorText(const QRectF& r) const
{
    const qreal t = cursorRelativeX(r);

    if (hasPhysicalScale()) {
        const qreal mm = relativeToThicknessMm(t);
        return QString::number(mm, 'f', 2) + " mm";
    }

    return QString::number(t, 'f', 3);
}

void AScanView::paint(QPainter* p)
{
    p->setRenderHint(QPainter::Antialiasing);

    const QRectF r = plotRect();
    if (r.width() <= 0.0 || r.height() <= 0.0) {
        return;
    }

    QVector<float> data;
    {
        QMutexLocker l(&samplesMutex_);
        data = samples_;
    }

    p->setPen(QPen(GRID, 1.0));
    for (int i = 0; i <= xDivisions_; ++i) {
        const qreal x = mapX(static_cast<qreal>(i) / xDivisions_, r);
        p->drawLine(QPointF(x, r.top()), QPointF(x, r.bottom()));
    }

    for (int i = 0; i <= H_GRID; ++i) {
        const qreal y = r.top() + r.height() * static_cast<qreal>(i) / H_GRID;
        p->drawLine(QPointF(r.left(), y), QPointF(r.right(), y));
    }

    p->setPen(QPen(AXIS, 1.0));
    p->drawLine(QPointF(r.left(), mapY(0.0f, r)), QPointF(r.right(), mapY(0.0f, r)));

    if (data.size() > 1) {
        QPainterPath path;
        const int last = data.size() - 1;

        path.moveTo(mapX(0.0, r), mapY(data[0], r));

        for (int i = 1; i <= last; ++i) {
            const qreal t = static_cast<qreal>(i) / last;
            path.lineTo(mapX(t, r), mapY(data[i], r));
        }

        p->setPen(QPen(SIGNAL_COLOR, SIGNAL_W, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        p->drawPath(path);
    }

    if (hasPhysicalScale()) {
        p->setPen(TEXT_COLOR);

        for (int i = 0; i <= xDivisions_; ++i) {
            const qreal t = static_cast<qreal>(i) / xDivisions_;
            const qreal x = mapX(t, r);
            const qreal mm = relativeToThicknessMm(t);
            const QString txt = QString::number(mm, 'f', 2) + " mm";

            p->drawText(QRectF(x - 30.0, r.bottom() + 5.0, 60.0, 20.0),
                        Qt::AlignHCenter,
                        txt);
        }
    }

    if (cursorVisible_) {
        const qreal x = std::clamp<qreal>(cursorX_, r.left(), r.right());

        p->setPen(QPen(CURSOR_LINE, CURSOR_W, Qt::DashLine));
        p->drawLine(QPointF(x, r.top()), QPointF(x, r.bottom()));

        const QString txt = cursorText(r);

        QFontMetrics fm(p->font());
        const int textWidth = fm.horizontalAdvance(txt);
        const int textHeight = fm.height();

        QRectF textRect(
            x - static_cast<qreal>(textWidth) * 0.5 - 6.0,
            r.bottom() + 3.0,
            static_cast<qreal>(textWidth) + 12.0,
            static_cast<qreal>(textHeight) + 4.0);

        if (textRect.left() < 0.0) {
            textRect.moveLeft(0.0);
        }
        if (textRect.right() > width()) {
            textRect.moveRight(width());
        }

        p->setPen(Qt::NoPen);
        p->setBrush(CURSOR_TEXT_BG);
        p->drawRoundedRect(textRect, 4.0, 4.0);

        p->setPen(CURSOR_TEXT_FG);
        p->drawText(textRect, Qt::AlignCenter, txt);
    }
}