#include "a_scan_view.h"
#include "a_scan_worker.h"

#include <QColor>
#include <QMetaObject>
#include <QMetaType>
#include <QMutexLocker>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

#include <algorithm>

#ifdef SIGNAL
#undef SIGNAL
#endif

#ifdef TEXT
#undef TEXT
#endif

#ifdef max
#undef max
#endif

namespace
{
constexpr qreal L = 8;
constexpr qreal R = 8;
constexpr qreal T = 8;
constexpr qreal B_NO_LABEL = 8;
constexpr qreal B_LABEL = 28;

constexpr int H_GRID = 8;

const QColor GRID(255,255,255,25);
const QColor AXIS(255,255,255,56);
const QColor SIGNAL("#6aa9ff");
const QColor TEXT("#a0a0a0");

constexpr qreal SIGNAL_W = 3.0;
}

AScanView::AScanView(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setAntialiasing(true);

    qRegisterMetaType<QVector<float>>();

    worker_ = new AScanWorker();
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this, &AScanView::requestStart, worker_, &AScanWorker::start);
    connect(this, &AScanView::requestStop, worker_, &AScanWorker::stop);
    connect(this, &AScanView::requestSampleCount, worker_, &AScanWorker::setSampleCount);

    connect(worker_, &AScanWorker::samplesReady,
            this, &AScanView::onSamplesReady);

    workerThread_.start();
    emit requestSampleCount(sampleCount_);
}

AScanView::~AScanView()
{
    emit requestStop();
    workerThread_.quit();
    workerThread_.wait();
}

// --- properties ---

DeviceController* AScanView::device() const { return device_; }

void AScanView::setDevice(DeviceController* v)
{
    if (device_ == v) return;

    if (active_) emit requestStop();

    device_ = v;

    QMetaObject::invokeMethod(worker_,
                              [=]() {
                                  worker_->setDevice(v);
                                  if (active_) worker_->start();
                              });

    update();
    emit deviceChanged();
}

int AScanView::sampleCount() const { return sampleCount_; }

void AScanView::setSampleCount(int v)
{
    if (v < 2 || v == sampleCount_) return;

    sampleCount_ = v;
    emit requestSampleCount(v);
    update();
    emit sampleCountChanged();
}

qreal AScanView::minY() const { return minY_; }
void AScanView::setMinY(qreal v){ minY_=v; update(); emit minYChanged(); }

qreal AScanView::maxY() const { return maxY_; }
void AScanView::setMaxY(qreal v){ maxY_=v; update(); emit maxYChanged(); }

bool AScanView::active() const { return active_; }

void AScanView::setActive(bool v)
{
    if (v == active_) return;
    active_ = v;
    if (v) emit requestStart();
    else emit requestStop();
    emit activeChanged();
}

qreal AScanView::soundVelocity() const { return soundVelocity_; }
void AScanView::setSoundVelocity(qreal v)
{
    v = std::max<qreal>(0, v);
    if (qFuzzyCompare(v, soundVelocity_)) return;
    soundVelocity_ = v;
    update();
    emit soundVelocityChanged();
}

qreal AScanView::timeRangeUs() const { return timeRangeUs_; }
void AScanView::setTimeRangeUs(qreal v)
{
    v = std::max<qreal>(0, v);
    if (qFuzzyCompare(v, timeRangeUs_)) return;
    timeRangeUs_ = v;
    update();
    emit timeRangeUsChanged();
}

int AScanView::xDivisions() const { return xDivisions_; }
void AScanView::setXDivisions(int v)
{
    v = std::max(1, v);
    if (v == xDivisions_) return;
    xDivisions_ = v;
    update();
    emit xDivisionsChanged();
}

// --- data ---

void AScanView::onSamplesReady(const QVector<float>& s)
{
    QMutexLocker l(&samplesMutex_);
    samples_ = s;
    update();
}

// --- math ---

bool AScanView::hasPhysicalScale() const
{
    return soundVelocity_ > 0 && timeRangeUs_ > 0;
}

qreal AScanView::relativeToThicknessMm(qreal t) const
{
    // t in [0..1]
    qreal timeSec = t * timeRangeUs_ * 1e-6;
    qreal meters = soundVelocity_ * timeSec * 0.5;
    return meters * 1000.0;
}

QRectF AScanView::plotRect() const
{
    qreal bottom = hasPhysicalScale() ? B_LABEL : B_NO_LABEL;

    return QRectF(
        L, T,
        width() - L - R,
        height() - T - bottom
        );
}

qreal AScanView::mapY(float v, const QRectF& r) const
{
    qreal t = (std::clamp<qreal>(v, minY_, maxY_) - minY_) / (maxY_ - minY_);
    return r.top() + r.height() * (1.0 - t);
}

qreal AScanView::mapX(qreal t, const QRectF& r) const
{
    return r.left() + r.width() * t;
}

// --- paint ---

void AScanView::paint(QPainter* p)
{
    p->setRenderHint(QPainter::Antialiasing);

    QRectF r = plotRect();
    if (r.width() <= 0 || r.height() <= 0) return;

    QVector<float> data;
    {
        QMutexLocker l(&samplesMutex_);
        data = samples_;
    }

    // grid
    p->setPen(QPen(GRID, 1));

    for (int i=0;i<=xDivisions_;++i) {
        qreal x = mapX((qreal)i/xDivisions_, r);
        p->drawLine(QPointF(x,r.top()), QPointF(x,r.bottom()));
    }

    for (int i=0;i<=H_GRID;++i) {
        qreal y = r.top()+r.height()*i/H_GRID;
        p->drawLine(QPointF(r.left(),y), QPointF(r.right(),y));
    }

    // axis 0
    p->setPen(QPen(AXIS,1));
    p->drawLine(QPointF(r.left(), mapY(0,r)), QPointF(r.right(), mapY(0,r)));

    // signal
    if (data.size()>1) {
        QPainterPath path;
        int last = data.size()-1;

        path.moveTo(mapX(0,r), mapY(data[0],r));

        for(int i=1;i<=last;++i){
            qreal t = (qreal)i/last;
            path.lineTo(mapX(t,r), mapY(data[i],r));
        }

        p->setPen(QPen(SIGNAL, SIGNAL_W, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        p->drawPath(path);
    }

    // labels (physical)
    if (hasPhysicalScale()) {
        p->setPen(TEXT);

        int last = std::max(1, sampleCount_-1);

        for (int i=0;i<=xDivisions_;++i){
            qreal t = (qreal)i/xDivisions_;
            qreal x = mapX(t,r);

            qreal mm = relativeToThicknessMm(t);

            QString text = QString::number(mm,'f',2)+" mm";

            p->drawText(
                QRectF(x-30, r.bottom()+5, 60, 20),
                Qt::AlignHCenter,
                text
                );
        }
    }
}