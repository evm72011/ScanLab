#include "a_scan_view.h"

#include "a_scan_worker.h"
#include "device.h"

#include <QColor>
#include <QMetaObject>
#include <QMetaType>
#include <QSGFlatColorMaterial>
#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGNode>

namespace
{
constexpr int GridNodeIndex = 0;
constexpr int AxisNodeIndex = 1;
constexpr int SignalNodeIndex = 2;

QSGGeometryNode* createLineNode(const QColor& color, float lineWidth)
{
    auto* node = new QSGGeometryNode();

    auto* geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0);
    geometry->setDrawingMode(QSGGeometry::DrawLines);
    geometry->setLineWidth(lineWidth);

    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    auto* material = new QSGFlatColorMaterial();
    material->setColor(color);

    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    return node;
}

QSGGeometryNode* createLineStripNode(const QColor& color, float lineWidth)
{
    auto* node = new QSGGeometryNode();

    auto* geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
#else
    geometry->setDrawingMode(GL_LINE_STRIP);
#endif
    geometry->setLineWidth(lineWidth);

    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    auto* material = new QSGFlatColorMaterial();
    material->setColor(color);

    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    return node;
}

QSGNode* ensureRootNode(QSGNode* oldNode)
{
    if (oldNode != nullptr) {
        return oldNode;
    }

    auto* root = new QSGNode();
    root->appendChildNode(createLineNode(QColor(255, 255, 255, 25), 1.0f));
    root->appendChildNode(createLineNode(QColor(255, 255, 255, 56), 1.0f));
    root->appendChildNode(createLineStripNode(QColor("#6aa9ff"), 1.0f));
    return root;
}

QSGGeometryNode* childGeometryNode(QSGNode* root, int index)
{
    QSGNode* child = root->firstChild();
    for (int i = 0; child != nullptr && i < index; ++i) {
        child = child->nextSibling();
    }

    return static_cast<QSGGeometryNode*>(child);
}
}

AScanView::AScanView(QQuickItem* parent)
    : QQuickItem(parent)
{
    qDebug() << "AScanView";
    setFlag(ItemHasContents, true);

    qRegisterMetaType<QVector<float>>("QVector<float>");

    worker_ = new AScanWorker();
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this, &AScanView::requestStart, worker_, &AScanWorker::start, Qt::QueuedConnection);
    connect(this, &AScanView::requestStop, worker_, &AScanWorker::stop, Qt::QueuedConnection);
    connect(this, &AScanView::requestSampleCount, worker_, &AScanWorker::setSampleCount, Qt::QueuedConnection);

    connect(
        worker_,
        &AScanWorker::samplesReady,
        this,
        &AScanView::onSamplesReady,
        Qt::QueuedConnection);

    connect(this, &QQuickItem::widthChanged, this, [this]() {
        markGridDirty();
        markSignalDirty();
        update();
    });

    connect(this, &QQuickItem::heightChanged, this, [this]() {
        markGridDirty();
        markSignalDirty();
        update();
    });

    workerThread_.start();
    emit requestSampleCount(sampleCount_);
}

AScanView::~AScanView()
{
    emit requestStop();
    workerThread_.quit();
    workerThread_.wait();
}

QObject* AScanView::device() const
{
    return device_;
}

void AScanView::setDevice(QObject* value)
{
    auto* typedDevice = qobject_cast<Device*>(value);
    if (device_ == typedDevice) {
        return;
    }

    if (device_ != nullptr) {
        disconnect(device_, nullptr, this, nullptr);
    }

    device_ = typedDevice;

    if (device_ != nullptr) {
        connect(device_, &QObject::destroyed, this, [this]() {
            device_ = nullptr;

            QMetaObject::invokeMethod(
                worker_,
                [this]() {
                    worker_->setDevice(nullptr);
                },
                Qt::QueuedConnection);

            if (active_) {
                emit requestStop();
            }

            emit deviceChanged();
        });
    }

    const bool shouldStart = active_;

    QMetaObject::invokeMethod(
        worker_,
        [this, typedDevice, shouldStart]() {
            worker_->setDevice(typedDevice);

            if (shouldStart) {
                worker_->start();
            }
        },
        Qt::QueuedConnection);

    emit deviceChanged();
}

int AScanView::sampleCount() const
{
    return sampleCount_;
}

void AScanView::setSampleCount(int value)
{
    if (sampleCount_ == value || value < 2) {
        return;
    }

    sampleCount_ = value;
    emit requestSampleCount(sampleCount_);
    emit sampleCountChanged();
}

qreal AScanView::minY() const
{
    return minY_;
}

void AScanView::setMinY(qreal value)
{
    if (qFuzzyCompare(minY_, value)) {
        return;
    }

    minY_ = value;
    markGridDirty();
    markSignalDirty();
    update();
    emit minYChanged();
}

qreal AScanView::maxY() const
{
    return maxY_;
}

void AScanView::setMaxY(qreal value)
{
    if (qFuzzyCompare(maxY_, value)) {
        return;
    }

    maxY_ = value;
    markGridDirty();
    markSignalDirty();
    update();
    emit maxYChanged();
}

bool AScanView::active() const
{
    return active_;
}

void AScanView::setActive(bool value)
{
    qDebug() << "setActive: " << value;
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

void AScanView::onSamplesReady(const QVector<float>& samples)
{
    {
        QMutexLocker locker(&samplesMutex_);
        samples_ = samples;
    }

    markSignalDirty();
    update();
}

QSGNode* AScanView::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*)
{
    QSGNode* root = ensureRootNode(oldNode);

    auto* gridNode = childGeometryNode(root, GridNodeIndex);
    auto* axisNode = childGeometryNode(root, AxisNodeIndex);
    auto* signalNode = childGeometryNode(root, SignalNodeIndex);

    const float w = static_cast<float>(width());
    const float h = static_cast<float>(height());

    if (w <= 0.0f || h <= 0.0f) {
        return root;
    }

    if (gridDirty_) {
        constexpr int vSteps = 10;
        constexpr int hSteps = 8;
        constexpr int lineCount = (vSteps + 1) + (hSteps + 1);
        constexpr int vertexCount = lineCount * 2;

        auto* geometry = gridNode->geometry();
        geometry->allocate(vertexCount);

        auto* vertices = geometry->vertexDataAsPoint2D();
        int index = 0;

        for (int i = 0; i <= vSteps; ++i) {
            const float x = w * static_cast<float>(i) / static_cast<float>(vSteps);
            vertices[index++].set(x, 0.0f);
            vertices[index++].set(x, h);
        }

        for (int i = 0; i <= hSteps; ++i) {
            const float y = h * static_cast<float>(i) / static_cast<float>(hSteps);
            vertices[index++].set(0.0f, y);
            vertices[index++].set(w, y);
        }

        gridNode->markDirty(QSGNode::DirtyGeometry);
        gridDirty_ = false;
    }

    if (axisNode != nullptr) {
        auto* geometry = axisNode->geometry();
        geometry->allocate(2);

        auto* vertices = geometry->vertexDataAsPoint2D();
        const float zeroY = static_cast<float>(mapY(0.0f, h));

        vertices[0].set(0.0f, zeroY);
        vertices[1].set(w, zeroY);

        axisNode->markDirty(QSGNode::DirtyGeometry);
    }

    if (signalDirty_) {
        QVector<float> data;
        {
            QMutexLocker locker(&samplesMutex_);
            data = samples_;
        }

        auto* geometry = signalNode->geometry();

        if (data.size() < 2) {
            geometry->allocate(0);
        } else {
            geometry->allocate(data.size());
            auto* vertices = geometry->vertexDataAsPoint2D();

            const int last = data.size() - 1;
            for (int i = 0; i < data.size(); ++i) {
                const float x = w * static_cast<float>(i) / static_cast<float>(last);
                const float y = static_cast<float>(mapY(data[i], h));
                vertices[i].set(x, y);
            }
        }

        signalNode->markDirty(QSGNode::DirtyGeometry);
        signalDirty_ = false;
    }

    return root;
}

qreal AScanView::mapY(float v, qreal h) const
{
    const qreal range = maxY_ - minY_;
    if (qFuzzyIsNull(range)) {
        return h * 0.5;
    }

    const qreal t = (v - minY_) / range;
    return h * (1.0 - t);
}

void AScanView::markGridDirty()
{
    gridDirty_ = true;
}

void AScanView::markSignalDirty()
{
    signalDirty_ = true;
}