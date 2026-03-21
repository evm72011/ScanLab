#include "b_scan_worker.h"

#include <QRandomGenerator>

#include <algorithm>
#include <cmath>
#include <cstring>

BScanWorker::BScanWorker(QObject* parent)
    : QObject(parent)
{
}

void BScanWorker::start()
{
    if (timer_ != nullptr) {
        return;
    }

    if (width_ < 2) {
        width_ = 2;
    }

    if (height_ < 2) {
        height_ = 2;
    }

    buffer_.resize(width_ * height_);
    buffer_.fill(0.0f);

    initializeFrame();

    timer_ = new QTimer(this);
    timer_->setInterval(40);

    connect(timer_, &QTimer::timeout, this, &BScanWorker::generate);
    timer_->start();
}

void BScanWorker::stop()
{
    if (timer_ == nullptr) {
        return;
    }

    timer_->stop();
    timer_->deleteLater();
    timer_ = nullptr;
}

void BScanWorker::setSize(int width, int height)
{
    if (width < 2 || height < 2) {
        return;
    }

    if (width_ == width && height_ == height) {
        return;
    }

    width_ = width;
    height_ = height;

    buffer_.resize(width_ * height_);
    buffer_.fill(0.0f);

    initializeFrame();
}

void BScanWorker::generate()
{
    if (width_ < 2 || height_ < 2 || buffer_.isEmpty()) {
        return;
    }

    phase_ += 0.15f;

    std::memmove(
        buffer_.data() + width_,
        buffer_.data(),
        sizeof(float) * static_cast<size_t>(width_) * static_cast<size_t>(height_ - 1));

    fillLine(buffer_.data(), 0);

    emit frameReady(toImage());
}

void BScanWorker::initializeFrame()
{
    if (width_ < 2 || height_ < 2) {
        return;
    }

    for (int y = 0; y < height_; ++y) {
        fillLine(buffer_.data() + y * width_, y);
        phase_ += 0.15f;
    }

    emit frameReady(toImage());
}

void BScanWorker::fillLine(float* line, int lineIndex)
{
    const float scanPos = height_ > 1
                              ? static_cast<float>(lineIndex) / static_cast<float>(height_ - 1)
                              : 0.0f;

    const float c1 = 0.20f + 0.015f * std::sin(phase_ * 0.7f + scanPos * 3.0f);
    const float c2 = 0.50f + 0.030f * std::sin(phase_ * 0.5f + scanPos * 5.0f);
    const float c3 = 0.78f + 0.020f * std::cos(phase_ * 0.9f + scanPos * 4.0f);

    const float a1 = 0.80f;
    const float a2 = 0.45f * (0.9f + 0.1f * std::sin(phase_));
    const float a3 = 0.60f * (0.9f + 0.1f * std::cos(phase_ * 0.7f));

    for (int x = 0; x < width_; ++x) {
        const float t = static_cast<float>(x) / static_cast<float>(width_ - 1);

        float v = 0.02f * static_cast<float>(QRandomGenerator::global()->generateDouble() - 0.5);

        v += pulse(t, c1, 0.010f, a1);
        v += pulse(t, c2, 0.018f, a2);
        v += pulse(t, c3, 0.025f, a3);

        v += 0.05f * std::sin(50.0f * t + phase_) * std::exp(-2.5f * t);

        line[x] = v;
    }
}

QImage BScanWorker::toImage() const
{
    QImage image(width_, height_, QImage::Format_Grayscale8);

    for (int y = 0; y < height_; ++y) {
        uchar* row = image.scanLine(y);

        for (int x = 0; x < width_; ++x) {
            const float v = buffer_[y * width_ + x];

            int gray = static_cast<int>((v + 1.0f) * 0.5f * 255.0f);
            gray = std::clamp(gray, 0, 255);

            row[x] = static_cast<uchar>(gray);
        }
    }

    return image;
}

float BScanWorker::pulse(float t, float center, float width, float amplitude) const
{
    const float x = (t - center) / width;
    return amplitude * std::exp(-x * x) * std::sin(16.0f * x);
}
