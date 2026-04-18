#pragma once

#include <QPointer>
#include <QHoverEvent>
#include <QQuickPaintedItem>
#include <qqmlintegration.h>

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

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor& value);

    void paint(QPainter* painter) override;
protected:
    void hoverMoveEvent(QHoverEvent* event) override;
    void hoverLeaveEvent(QHoverEvent* event) override;

private:
    QRectF plotRect() const;
    void paintBackground(QPainter* painter, const QRectF& rect);
    void paintGrid(QPainter* painter, const QRectF& rect);
    void paintSignal(QPainter* painter, const QRectF& rect, const QVariantList& samples);
    qreal mapSampleY(double value, const QRectF& rect) const;
    qreal mapSampleX(int index, int count, const QRectF& rect) const;
    void paintCursor(QPainter* painter, const QRectF& rect);

signals:
    void facadeChanged();
    void lineColorChanged();
    void gridColorChanged();
    void markerColorChanged();
    void backgroundColorChanged();

private:
    QPointer<AScanFacade> facade_;
    QColor lineColor_ = Qt::green;
    QColor gridColor_ = Qt::gray;
    QColor backgroundColor_ = Qt::black;
    QColor markerColor_ = Qt::yellow;

    bool cursorVisible_ = false;
    qreal cursorX_ = 0.0;
};
