#pragma once

#include <QMutex>
#include <QPointer>
#include <QQuickPaintedItem>
#include <QThread>
#include <QVector>
#include <qqmlintegration.h>


class AScanWorker;
class QHoverEvent;

class AScanView : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
/*
    Q_PROPERTY(DeviceFacade* device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(int sampleCount READ sampleCount WRITE setSampleCount NOTIFY sampleCountChanged)
    Q_PROPERTY(qreal minY READ minY WRITE setMinY NOTIFY minYChanged)
    Q_PROPERTY(qreal maxY READ maxY WRITE setMaxY NOTIFY maxYChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

    Q_PROPERTY(qreal soundVelocity READ soundVelocity WRITE setSoundVelocity NOTIFY soundVelocityChanged)
    Q_PROPERTY(qreal timeRangeUs READ timeRangeUs WRITE setTimeRangeUs NOTIFY timeRangeUsChanged)
    Q_PROPERTY(qreal timeStartUs READ timeStartUs WRITE setTimeStartUs NOTIFY timeStartUsChanged)

    Q_PROPERTY(int xDivisions READ xDivisions WRITE setXDivisions NOTIFY xDivisionsChanged)
*/
public:
    explicit AScanView(QQuickItem* parent = nullptr);
    ~AScanView() override;
/*
    DeviceFacade* device() const;
    void setDevice(DeviceFacade* value);

    int sampleCount() const;
    void setSampleCount(int value);

    qreal minY() const;
    void setMinY(qreal value);

    qreal maxY() const;
    void setMaxY(qreal value);

    bool active() const;
    void setActive(bool value);

    qreal soundVelocity() const;
    void setSoundVelocity(qreal value);

    qreal timeRangeUs() const;
    void setTimeRangeUs(qreal value);

    qreal timeStartUs() const;
    void setTimeStartUs(qreal value);

    int xDivisions() const;
    void setXDivisions(int value);

    void paint(QPainter* painter) override;

signals:
    void deviceChanged();
    void sampleCountChanged();
    void minYChanged();
    void maxYChanged();
    void activeChanged();

    void soundVelocityChanged();
    void timeRangeUsChanged();
    void timeStartUsChanged();
    void xDivisionsChanged();

    void requestStart();
    void requestStop();
    void requestSampleCount(int value);

private slots:
    void onSamplesReady(const QVector<float>& samples);

protected:
    void hoverMoveEvent(QHoverEvent* event) override;
    void hoverLeaveEvent(QHoverEvent* event) override;

private:
    QRectF plotRect() const;

    qreal mapY(float value, const QRectF& plotRect) const;
    qreal mapX(qreal t, const QRectF& plotRect) const;

    bool hasPhysicalScale() const;
    qreal relativeToThicknessMm(qreal t) const;
    qreal cursorRelativeX(const QRectF& plotRect) const;
    QString cursorText(const QRectF& plotRect) const;

private:
    QVector<float> samples_;
    mutable QMutex samplesMutex_;

    QPointer<DeviceFacade> device_;

    int sampleCount_ = 512;
    qreal minY_ = -1.0;
    qreal maxY_ = 1.0;
    bool active_ = false;

    qreal soundVelocity_ = 0.0;
    qreal timeRangeUs_ = 0.0;
    qreal timeStartUs_ = 0.0;

    int xDivisions_ = 10;

    bool cursorVisible_ = false;
    qreal cursorX_ = 0.0;

    QThread workerThread_;
    AScanWorker* worker_ = nullptr;
*/
};