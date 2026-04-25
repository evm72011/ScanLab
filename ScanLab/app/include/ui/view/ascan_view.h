#pragma once

#include <QColor>
#include <QPointer>
#include <QQuickPaintedItem>
#include <QVector>
#include <qqmlintegration.h>

#include "scanlab/acquisition/ascan/envelope_point.h"

class AScanFacade;

class AScanView : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(AScanFacade* facade READ facade WRITE setFacade NOTIFY facadeChanged)

    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(QColor markerColor READ markerColor WRITE setMarkerColor NOTIFY markerColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor axisTextColor READ axisTextColor WRITE setAxisTextColor NOTIFY axisTextColorChanged)
    Q_PROPERTY(qreal minThicknessMm READ minThicknessMm WRITE setMinThicknessMm NOTIFY minThicknessMmChanged)
    Q_PROPERTY(qreal maxThicknessMm READ maxThicknessMm WRITE setMaxThicknessMm NOTIFY maxThicknessMmChanged)

public:
    explicit AScanView(QQuickItem* parent = nullptr);
    ~AScanView() override;

    AScanFacade* facade() const;
    void setFacade(AScanFacade* value);

    QColor lineColor() const;
    void setLineColor(const QColor& value);

    QColor gridColor() const;
    void setGridColor(const QColor& value);

    QColor markerColor() const;
    void setMarkerColor(const QColor& value);

    QColor axisTextColor() const;
    void setAxisTextColor(const QColor& value);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor& value);

    qreal minThicknessMm() const;
    void setMinThicknessMm(qreal value);

    qreal maxThicknessMm() const;
    void setMaxThicknessMm(qreal value);

    void paint(QPainter* painter) override;

protected:
    void hoverMoveEvent(QHoverEvent* event) override;
    void hoverLeaveEvent(QHoverEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    using EnvelopePoint = scanlab::acquisition::ascan::EnvelopePoint;

    QRectF plotRect() const;
    void paintBackground(QPainter* painter, const QRectF& rect);
    void paintGrid(QPainter* painter, const QRectF& rect);
    void paintXAxisLabels(QPainter* painter, const QRectF& rect);
    void paintSignal(QPainter* painter, const QRectF& rect, const QVector<EnvelopePoint>& samples);
    void paintCursor(QPainter* painter, const QRectF& rect);
    void paintCursorLabel(QPainter* painter, const QRectF& rect);

    void applyZoom(qreal cursorX, qreal factor);
    void updateCropMargins();

    qreal mapSampleY(double value, const QRectF& rect) const;
    qreal mapSampleX(int index, int count, const QRectF& rect) const;
    qreal cursorThicknessMm(const QRectF& rect) const;

signals:
    void facadeChanged();
    void lineColorChanged();
    void gridColorChanged();
    void backgroundColorChanged();
    void markerColorChanged();
    void axisTextColorChanged();
    void minThicknessMmChanged();
    void maxThicknessMmChanged();

private:
    QPointer<AScanFacade> facade_;

    QColor lineColor_ = Qt::green;
    QColor gridColor_ = Qt::gray;
    QColor backgroundColor_ = Qt::black;
    QColor markerColor_ = Qt::yellow;
    QColor axisTextColor_ = Qt::gray;

    int xDivisions_ = 10;
    int yDivisions_ = 10;
    qreal minThicknessMm_ = 0.0;
    qreal maxThicknessMm_ = 20.0;

    qreal visibleLeft_ = 0.0;
    qreal visibleRight_ = 1.0;
    qreal minVisibleWidth_ = 0.01;

    bool dragging_ = false;
    qreal dragStartX_ = 0.0;
    qreal dragStartVisibleLeft_ = 0.0;
    qreal dragStartVisibleRight_ = 1.0;

    bool cursorVisible_ = false;
    qreal cursorX_ = 0.0;

    QMetaObject::Connection frameReadyConnection_;
};