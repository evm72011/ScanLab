#include "a_scan_worker.h"

#include <QtMath>
#include <QRandomGenerator>

AScanWorker::AScanWorker(QObject* parent)
    : QObject(parent)
{
}

void AScanWorker::start()
{
    if (timer_ != nullptr) {
        return;
    }

    timer_ = new QTimer(this);
    timer_->setInterval(40);

    connect(timer_, &QTimer::timeout, this, &AScanWorker::generate);
    timer_->start();
}

void AScanWorker::stop()
{
    if (timer_ == nullptr) {
        return;
    }

    timer_->stop();
    timer_->deleteLater();
    timer_ = nullptr;
}

void AScanWorker::setSampleCount(int value)
{
    if (value > 1) {
        sampleCount_ = value;
    }
}

void AScanWorker::generate()
{
    phase_ += 0.18f;

    QVector<float> result;
    result.reserve(sampleCount_);

    for (int i = 0; i < sampleCount_; ++i) {
        const float t = static_cast<float>(i) / static_cast<float>(sampleCount_ - 1);

        float y = 0.03f * (QRandomGenerator::global()->generateDouble() - 0.5f);

        y += pulse(t, 0.08f, 0.010f, 0.85f);
        y += pulse(t, 0.34f, 0.018f, 0.45f * (0.9f + 0.1f * std::sin(phase_)));
        y += pulse(t, 0.72f, 0.025f, 0.65f * (0.9f + 0.1f * std::cos(phase_ * 0.7f)));

        y += 0.08f * std::sin(60.0f * t + phase_) * std::exp(-3.2f * t);

        result.push_back(y);
    }

    emit samplesReady(result);
}

float AScanWorker::pulse(float t, float center, float width, float amplitude)
{
    const float x = (t - center) / width;
    return amplitude * std::exp(-x * x) * std::sin(18.0f * x);
}
