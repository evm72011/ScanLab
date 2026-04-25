#include "ui/view/ascan_view.h"

#include "ui/acquisition/ascan_facade.h"

#include <QHoverEvent>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QWheelEvent>

AScanView::AScanView(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setOpaquePainting(true);
}

AScanView::~AScanView() = default;

AScanFacade* AScanView::facade() const
{
    return facade_;
}

void AScanView::setFacade(AScanFacade* value)
{
    if (facade_ == value) {
        return;
    }

    if (frameReadyConnection_) {
        disconnect(frameReadyConnection_);
    }

    facade_ = value;

    if (facade_) {
        frameReadyConnection_ = connect(
            facade_,
            &AScanFacade::frameReady,
            this,
            [this]() {
                update();
            },
            Qt::QueuedConnection);
    }

    emit facadeChanged();
    update();
}

QColor AScanView::lineColor() const
{
    return lineColor_;
}

void AScanView::setLineColor(const QColor& value)
{
    if (lineColor_ == value) {
        return;
    }

    lineColor_ = value;
    emit lineColorChanged();
    update();
}

QColor AScanView::gridColor() const
{
    return gridColor_;
}

void AScanView::setGridColor(const QColor& value)
{
    if (gridColor_ == value) {
        return;
    }

    gridColor_ = value;
    emit gridColorChanged();
    update();
}

QColor AScanView::markerColor() const
{
    return markerColor_;
}

void AScanView::setMarkerColor(const QColor& value)
{
    if (markerColor_ == value) {
        return;
    }

    markerColor_ = value;
    emit markerColorChanged();
    update();
}

QColor AScanView::axisTextColor() const
{
    return axisTextColor_;
}

void AScanView::setAxisTextColor(const QColor& value)
{
    if (axisTextColor_ == value) {
        return;
    }

    axisTextColor_ = value;
    emit axisTextColorChanged();
    update();
}

QColor AScanView::backgroundColor() const
{
    return backgroundColor_;
}

void AScanView::setBackgroundColor(const QColor& value)
{
    if (backgroundColor_ == value) {
        return;
    }

    backgroundColor_ = value;
    emit backgroundColorChanged();
    update();
}

qreal AScanView::minThicknessMm() const
{
    return minThicknessMm_;
}

void AScanView::setMinThicknessMm(qreal value)
{
    if (qFuzzyCompare(minThicknessMm_, value)) {
        return;
    }

    minThicknessMm_ = value;
    emit minThicknessMmChanged();
    update();
}

qreal AScanView::maxThicknessMm() const
{
    return maxThicknessMm_;
}

void AScanView::setMaxThicknessMm(qreal value)
{
    if (qFuzzyCompare(maxThicknessMm_, value)) {
        return;
    }

    maxThicknessMm_ = value;
    emit maxThicknessMmChanged();
    update();
}

void AScanView::paint(QPainter* painter)
{
    if (!painter) {
        return;
    }

    const auto rect = plotRect();

    paintBackground(painter, boundingRect());
    paintGrid(painter, rect);
    paintXAxisLabels(painter, rect);

    if (facade_) {
        paintSignal(painter, rect, facade_->samplesSnapshot());
    }

    paintCursor(painter, rect);
    paintCursorLabel(painter, rect);
}

void AScanView::hoverMoveEvent(QHoverEvent* event)
{
    if (!event) {
        return;
    }

    cursorVisible_ = true;
    cursorX_ = event->position().x();
    update();
}

void AScanView::hoverLeaveEvent(QHoverEvent* event)
{
    Q_UNUSED(event);

    cursorVisible_ = false;
    update();
}


void AScanView::wheelEvent(QWheelEvent* event)
{
    if (!event) {
        return;
    }

    const auto rect = plotRect();
    const qreal x = event->position().x();

    if (x < rect.left() || x > rect.right()) {
        return;
    }

    cursorVisible_ = true;
    cursorX_ = x;

    const qreal factor = event->angleDelta().y() > 0
                             ? 0.8   // zoom in
                             : 1.25; // zoom out

    applyZoom(x, factor);

    event->accept();
}

void AScanView::applyZoom(qreal cursorX, qreal factor)
{
    const auto rect = plotRect();

    if (rect.width() <= 0.0) {
        return;
    }

    const qreal cursorNorm =
        qBound<qreal>(0.0, (cursorX - rect.left()) / rect.width(), 1.0);

    const qreal oldLeft = visibleLeft_;
    const qreal oldRight = visibleRight_;
    const qreal oldWidth = oldRight - oldLeft;

    qreal newWidth = oldWidth * factor;
    newWidth = qBound(minVisibleWidth_, newWidth, 1.0);

    const qreal centerInSource = oldLeft + cursorNorm * oldWidth;

    qreal newLeft = centerInSource - cursorNorm * newWidth;
    qreal newRight = newLeft + newWidth;

    if (newLeft < 0.0) {
        newRight -= newLeft;
        newLeft = 0.0;
    }

    if (newRight > 1.0) {
        newLeft -= newRight - 1.0;
        newRight = 1.0;
    }

    visibleLeft_ = qBound<qreal>(0.0, newLeft, 1.0);
    visibleRight_ = qBound<qreal>(0.0, newRight, 1.0);

    updateCropMargins();
    update();
}

void AScanView::updateCropMargins()
{
    if (!facade_) {
        return;
    }

    facade_->setCropMargins(
        visibleLeft_,
        1.0 - visibleRight_);
}

QRectF AScanView::plotRect() const
{
    constexpr qreal left = 16.0;
    constexpr qreal top = 12.0;
    constexpr qreal right = 12.0;
    constexpr qreal bottom = 28.0;

    return QRectF(
        left,
        top,
        qMax(0.0, width() - left - right),
        qMax(0.0, height() - top - bottom));
}

void AScanView::paintBackground(QPainter* painter, const QRectF& rect)
{
    painter->fillRect(rect, backgroundColor_);
}

void AScanView::paintGrid(QPainter* painter, const QRectF& rect)
{
    painter->save();

    QPen pen(gridColor_);
    pen.setWidthF(1.0);
    painter->setPen(pen);

    if (xDivisions_ > 0) {
        for (int i = 0; i <= xDivisions_; ++i) {
            const qreal x =
                rect.left() +
                (static_cast<qreal>(i) / static_cast<qreal>(xDivisions_)) * rect.width();

            painter->drawLine(
                QPointF(x, rect.top()),
                QPointF(x, rect.bottom()));
        }
    }

    if (yDivisions_ > 0) {
        for (int i = 0; i <= yDivisions_; ++i) {
            const qreal y =
                rect.top() +
                (static_cast<qreal>(i) / static_cast<qreal>(yDivisions_)) * rect.height();

            painter->drawLine(
                QPointF(rect.left(), y),
                QPointF(rect.right(), y));
        }
    }

    painter->restore();
}

void AScanView::paintXAxisLabels(QPainter* painter, const QRectF& rect)
{
    painter->save();
    painter->setPen(axisTextColor_);

    if (xDivisions_ <= 0) {
        painter->restore();
        return;
    }

    const double step =
        (maxThicknessMm_ - minThicknessMm_) /
        static_cast<double>(xDivisions_);

    for (int i = 0; i <= xDivisions_; ++i) {
        const double x =
            rect.left() +
            (static_cast<double>(i) / static_cast<double>(xDivisions_)) * rect.width();

        const double value =
            minThicknessMm_ + static_cast<double>(i) * step;

        const QRectF textRect(
            x - 24.0,
            rect.bottom() + 4.0,
            48.0,
            16.0);

        painter->drawText(
            textRect,
            Qt::AlignHCenter | Qt::AlignTop,
            QString::number(value, 'f', 1));
    }

    painter->restore();
}

void AScanView::paintSignal(
    QPainter* painter,
    const QRectF& rect,
    const QVector<EnvelopePoint>& samples)
{
    if (samples.isEmpty()) {
        return;
    }

    painter->save();

    QPen pen(lineColor_);
    pen.setWidthF(2.0);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing, false);

    const int count = samples.size();

    QPainterPath centerPath;

    const auto centerValue = [](const EnvelopePoint& p) {
        return (p.min + p.max) * 0.5f;
    };

    centerPath.moveTo(
        mapSampleX(0, count, rect),
        mapSampleY(centerValue(samples[0]), rect));

    for (int i = 1; i < count; ++i) {
        centerPath.lineTo(
            mapSampleX(i, count, rect),
            mapSampleY(centerValue(samples[i]), rect));
    }

    painter->drawPath(centerPath);

    for (int i = 0; i < count; ++i) {
        const auto& sample = samples[i];

        const qreal yMin = mapSampleY(sample.min, rect);
        const qreal yMax = mapSampleY(sample.max, rect);

        if (qAbs(yMin - yMax) < 5.0) {
            continue;
        }

        const qreal x = mapSampleX(i, count, rect);

        painter->drawLine(
            QPointF(x, yMin),
            QPointF(x, yMax));
    }

    painter->restore();
}

void AScanView::paintCursor(QPainter* painter, const QRectF& rect)
{
    if (!cursorVisible_) {
        return;
    }

    if (cursorX_ < rect.left() || cursorX_ > rect.right()) {
        return;
    }

    painter->save();

    QPen pen(markerColor_);
    pen.setWidthF(1.0);
    pen.setStyle(Qt::DashLine);

    painter->setPen(pen);

    painter->drawLine(
        QPointF(cursorX_, rect.top()),
        QPointF(cursorX_, rect.bottom()));

    painter->restore();
}

void AScanView::paintCursorLabel(QPainter* painter, const QRectF& rect)
{
    if (!cursorVisible_) {
        return;
    }

    if (cursorX_ < rect.left() || cursorX_ > rect.right()) {
        return;
    }

    painter->save();

    const auto thickness = cursorThicknessMm(rect);
    const QString text = QString::number(thickness, 'f', 1) + " mm";

    const QRectF textRect(
        qMin(cursorX_ + 6.0, rect.right() - 70.0),
        rect.top() + 6.0,
        70.0,
        18.0);

    painter->setPen(markerColor_);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

    painter->restore();
}

qreal AScanView::mapSampleY(double value, const QRectF& rect) const
{
    const double normalized = qBound(0.0, (value + 1.0) * 0.5, 1.0);
    return rect.bottom() - normalized * rect.height();
}

qreal AScanView::mapSampleX(int index, int count, const QRectF& rect) const
{
    if (count <= 1) {
        return rect.left();
    }

    return rect.left() +
           (static_cast<qreal>(index) / static_cast<qreal>(count - 1)) * rect.width();
}

qreal AScanView::cursorThicknessMm(const QRectF& rect) const
{
    if (rect.width() <= 0.0) {
        return minThicknessMm_;
    }

    const qreal normalized =
        qBound<qreal>(0.0, (cursorX_ - rect.left()) / rect.width(), 1.0);

    return minThicknessMm_ + normalized * (maxThicknessMm_ - minThicknessMm_);
}
