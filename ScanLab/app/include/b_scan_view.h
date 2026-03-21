#pragma once

#include <QImage>
#include <QMutex>
#include <QPainter>
#include <QQuickPaintedItem>
#include <QThread>
#include <qqmlintegration.h>

class BScanWorker;

class BScanView : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
    explicit BScanView(QQuickItem* parent = nullptr);
    ~BScanView() override;

    bool active() const;
    void setActive(bool value);

    void paint(QPainter* painter) override;

signals:
    void activeChanged();

    void requestStart();
    void requestStop();
    void requestResize(int width, int height);

private slots:
    void onFrameReady(const QImage& image);

private:
    QMutex imageMutex_;
    QImage image_;
    bool active_ = false;

    QThread workerThread_;
    BScanWorker* worker_ = nullptr;
};
