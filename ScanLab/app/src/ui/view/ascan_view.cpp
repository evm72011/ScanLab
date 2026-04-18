#include "ui/view/ascan_view.h"

#include "ui/acquisition/ascan_facade.h"

#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QVariantList>
#include <algorithm>

AScanView::AScanView(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    setAcceptHoverEvents(true);
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

    if (facade_) {
        disconnect(facade_, nullptr, this, nullptr);
    }

    facade_ = value;

    if (facade_) {
        connect(
            facade_,
            &AScanFacade::samplesChanged,
            this,
            [this]() {
                update();
            });

        connect(
            facade_,
            &AScanFacade::runningChanged,
            this,
            [this]() {
                update();
            });
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
    if (lineColor_ == value)
        return;

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
    if (gridColor_ == value)
        return;

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
    if (markerColor_ == value)
        return;

    markerColor_ = value;
    emit markerColorChanged();
    update();
}

QColor AScanView::backgroundColor() const
{
    return backgroundColor_;
}

void AScanView::setBackgroundColor(const QColor& value)
{
    if (backgroundColor_ == value)
        return;

    backgroundColor_ = value;
    emit backgroundColorChanged();
    update();
}

QRectF AScanView::plotRect() const
{
    return boundingRect().adjusted(0.5, 0.5, -0.5, -0.5);
}

void AScanView::paint(QPainter* painter)
{
    const auto rect = plotRect();
    if (rect.width() <= 0.0 || rect.height() <= 0.0) {
        return;
    }

    painter->setRenderHint(QPainter::Antialiasing, true);

    paintBackground(painter, rect);
    paintGrid(painter, rect);

    if (!facade_) {
        return;
    }

    const auto samples = facade_->samples();
    if (samples.isEmpty()) {
        return;
    }

    paintSignal(painter, rect, samples);
    paintCursor(painter, rect);
}

void AScanView::paintBackground(QPainter* painter, const QRectF& rect)
{
    painter->fillRect(rect, backgroundColor_);
}

void AScanView::paintGrid(QPainter* painter, const QRectF& rect)
{
    QPen gridPen(gridColor_);
    gridPen.setWidthF(1.0);
    painter->setPen(gridPen);

    const int xDivisions = 10;
    const int yDivisions = 10;

    for (int i = 0; i <= xDivisions; ++i) {
        const double x =
            rect.left() +
            (static_cast<double>(i) / static_cast<double>(xDivisions)) * rect.width();

        painter->drawLine(
            QPointF(x, rect.top()),
            QPointF(x, rect.bottom()));
    }

    for (int i = 0; i <= yDivisions; ++i) {
        const double y =
            rect.top() +
            (static_cast<double>(i) / static_cast<double>(yDivisions)) * rect.height();

        painter->drawLine(
            QPointF(rect.left(), y),
            QPointF(rect.right(), y));
    }
}

void AScanView::paintSignal(QPainter* painter, const QRectF& rect, const QVariantList& samples)
{
    QPen linePen(lineColor_);
    linePen.setWidthF(2.0);
    painter->setPen(linePen);

    const int count = samples.size();
    if (count == 1) {
        const auto value = samples.first().toDouble();
        painter->drawPoint(QPointF(rect.left(), mapSampleY(value, rect)));
        return;
    }

    QPainterPath path;

    for (int i = 0; i < count; ++i) {
        const double x = mapSampleX(i, count, rect);
        const double y = mapSampleY(samples.at(i).toDouble(), rect);
        const QPointF point(x, y);

        if (i == 0) {
            path.moveTo(point);
        } else {
            path.lineTo(point);
        }
    }

    painter->drawPath(path);
}

void AScanView::paintCursor(QPainter* painter, const QRectF& rect)
{
    if (!cursorVisible_) {
        return;
    }

    const qreal x = std::clamp(cursorX_, rect.left(), rect.right());

    QPen cursorPen(QColor("#FFD54A"));
    cursorPen.setWidthF(1.0);
    cursorPen.setStyle(Qt::DashLine);
    painter->setPen(cursorPen);

    painter->drawLine(
        QPointF(x, rect.top()),
        QPointF(x, rect.bottom()));
}

qreal AScanView::mapSampleY(double value, const QRectF& rect) const
{
    const double normalized = std::clamp((value + 1.0) * 0.5, 0.0, 1.0);
    return rect.bottom() - normalized * rect.height();
}

qreal AScanView::mapSampleX(int index, int count, const QRectF& rect) const
{
    if (count <= 1) {
        return rect.left();
    }

    return rect.left() +
           (static_cast<double>(index) / static_cast<double>(count - 1)) * rect.width();
}

void AScanView::hoverMoveEvent(QHoverEvent* event)
{
    cursorVisible_ = true;
    cursorX_ = event->position().x();
    update();

    QQuickPaintedItem::hoverMoveEvent(event);
}

void AScanView::hoverLeaveEvent(QHoverEvent* event)
{
    cursorVisible_ = false;
    update();

    QQuickPaintedItem::hoverLeaveEvent(event);
}
