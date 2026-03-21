#pragma once

#include <QMutex>
#include <QQuickItem>
#include <QThread>
#include <QVector>
#include <qqmlintegration.h>

class QSGNode;
class AScanWorker;

class AScanView : public QQuickItem
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

protected:
    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* updatePaintNodeData) override;

private slots:
    void onSamplesReady(const QVector<float>& samples);

private:
    qreal mapY(float v, qreal h) const;
    void markGridDirty();
    void markSignalDirty();

private:
    QVector<float> samples_;
    mutable QMutex samplesMutex_;

    int sampleCount_ = 512;
    qreal minY_ = -1.0;
    qreal maxY_ = 1.0;
    bool active_ = false;

    bool gridDirty_ = true;
    bool signalDirty_ = true;

    QThread workerThread_;
    AScanWorker* worker_ = nullptr;
};
