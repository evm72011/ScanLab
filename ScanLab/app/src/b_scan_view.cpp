#include "b_scan_view.h"
#include "b_scan_worker.h"

#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QSGTexture>
#include <QRunnable>

namespace
{
class TextureCleanupJob final : public QRunnable
{
public:
    explicit TextureCleanupJob(QSGTexture* texture)
        : texture_(texture)
    {
    }

    void run() override
    {
        delete texture_;
    }

private:
    QSGTexture* texture_ = nullptr;
};
}

BScanView::BScanView(QQuickItem* parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);

    worker_ = new BScanWorker();
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this, &BScanView::requestStart, worker_, &BScanWorker::start, Qt::QueuedConnection);
    connect(this, &BScanView::requestStop, worker_, &BScanWorker::stop, Qt::QueuedConnection);
    connect(this, &BScanView::requestResize, worker_, &BScanWorker::setSize, Qt::QueuedConnection);

    connect(worker_, &BScanWorker::frameReady,
            this, &BScanView::onFrameReady,
            Qt::QueuedConnection);

    connect(this, &QQuickItem::widthChanged, this, [this]() {
        emit requestResize(static_cast<int>(width()), static_cast<int>(height()));
    });

    connect(this, &QQuickItem::heightChanged, this, [this]() {
        emit requestResize(static_cast<int>(width()), static_cast<int>(height()));
    });

    workerThread_.start();
    emit requestResize(static_cast<int>(width()), static_cast<int>(height()));
}

BScanView::~BScanView()
{
    emit requestStop();
    workerThread_.quit();
    workerThread_.wait();
}

bool BScanView::active() const
{
    return active_;
}

void BScanView::setActive(bool value)
{
    if (active_ == value) {
        return;
    }

    active_ = value;

    if (active_) {
        emit requestStart();
    } else {
        emit requestStop();
    }

    emit activeChanged();
}

void BScanView::onFrameReady(const QImage& image)
{
    image_ = image;
    imageDirty_ = true;
    update();
}

QSGNode* BScanView::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*)
{
    if (window() == nullptr || image_.isNull()) {
        delete oldNode;
        return nullptr;
    }

    auto* node = static_cast<QSGSimpleTextureNode*>(oldNode);
    if (node == nullptr) {
        node = new QSGSimpleTextureNode();
        node->setOwnsTexture(true);
    }

    if (imageDirty_) {
        QSGTexture* newTexture = window()->createTextureFromImage(
            image_,
            QQuickWindow::TextureIsOpaque);

        if (newTexture == nullptr) {
            delete node;
            return nullptr;
        }

        if (node->texture() != nullptr) {
            delete node->texture();
        }

        node->setTexture(newTexture);
        node->setRect(boundingRect());

        imageDirty_ = false;
    } else {
        node->setRect(boundingRect());
    }

    return node;
}

void BScanView::releaseResources()
{
    if (window() != nullptr) {
        window()->scheduleRenderJob(
            new TextureCleanupJob(nullptr),
            QQuickWindow::BeforeSynchronizingStage);
    }
}

void BScanView::invalidateSceneGraph()
{
}
