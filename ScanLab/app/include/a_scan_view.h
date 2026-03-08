#pragma once

#include <QMutex>
#include <QThread>
#include <QVector>
#include <QQuickPaintedItem>
#include <qqmlintegration.h>

class AScanWorker;

class AScanView : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int sampleCount READ sampleCount WRITE setSampleCount NOTIFY sampleCountChanged)
    Q_PROPERTY(qreal minY READ minY WRITE setMinY NOTIFY minYChanged)
    Q_PROPERTY(qreal maxY READ maxY WRITE setMaxY NOTIFY maxYChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
    explicit AScanView(QQuickItem* parent = nullptr);
    ~AScanView() override;

    void paint(QPainter* painter) override;

    int sampleCount() const;
    void setSampleCount(int value);

    qreal minY() const;
    void setMinY(qreal value);

    qreal maxY() const;
    void setMaxY(qreal value);

    bool active() const;
    void setActive(bool value);

signals:
    void sampleCountChanged();
    void minYChanged();
    void maxYChanged();
    void activeChanged();

    void requestStart();
    void requestStop();
    void requestSampleCount(int value);

private slots:
    void onSamplesReady(const QVector<float>& samples);

private:
    void drawGrid(QPainter& p, const QRectF& r);
    void drawAxes(QPainter& p, const QRectF& r);
    void drawSignal(QPainter& p, const QRectF& r);
    qreal mapY(float v, qreal h) const;

private:
    QVector<float> samples_;
    mutable QMutex samplesMutex_;

    int sampleCount_ = 512;
    qreal minY_ = -1.0;
    qreal maxY_ = 1.0;
    bool active_ = false;

    QThread workerThread_;
    AScanWorker* worker_ = nullptr;
};
