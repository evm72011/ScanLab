#pragma once

#include <QImage>
#include <QQuickItem>
#include <QThread>
#include <qqmlintegration.h>

class BScanWorker;

class BScanView : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
    explicit BScanView(QQuickItem* parent = nullptr);
    ~BScanView() override;

    bool active() const;
    void setActive(bool value);

signals:
    void activeChanged();

    void requestStart();
    void requestStop();
    void requestResize(int width, int height);

protected:
    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* updatePaintNodeData) override;
    void releaseResources() override;

private slots:
    void onFrameReady(const QImage& image);
    void invalidateSceneGraph();

private:
    QImage image_;
    bool imageDirty_ = false;
    bool active_ = false;

    QThread workerThread_;
    BScanWorker* worker_ = nullptr;
};
