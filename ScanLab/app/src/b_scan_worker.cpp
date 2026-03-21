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
    delete timer_;
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

    // сдвиг вниз (новая строка сверху)
    std::memmove(
        buffer_.data() + width_,
        buffer_.data(),
        sizeof(float) * static_cast<size_t>(width_) * static_cast<size_t>(height_ - 1));

    fillLine(buffer_.data());

    emit frameReady(toImage());
}

void BScanWorker::initializeFrame()
{
    if (width_ < 2 || height_ < 2) {
        return;
    }

    for (int y = 0; y < height_; ++y) {
        fillLine(buffer_.data() + y * width_);
    }

    emit frameReady(toImage());
}

void BScanWorker::fillLine(float* line)
{
    // фиксированные отражатели (вертикальные линии)
    const float c1 = 0.20f;
    const float c2 = 0.50f;
    const float c3 = 0.78f;

    const float a1 = 0.9f;
    const float a2 = 0.6f;
    const float a3 = 0.75f;

    for (int x = 0; x < width_; ++x) {
        const float t = static_cast<float>(x) / static_cast<float>(width_ - 1);

        // небольшой шум
        float v = 0.03f * static_cast<float>(QRandomGenerator::global()->generateDouble() - 0.5);

        // отражатели
        v += pulse(t, c1, 0.008f, a1);
        v += pulse(t, c2, 0.012f, a2);
        v += pulse(t, c3, 0.020f, a3);

        // экспоненциальное затухание по глубине (как в реальном ультразвуке)
        v *= std::exp(-1.5f * t);

        line[x] = v;
    }
}

float BScanWorker::pulse(float t, float center, float width, float amplitude) const
{
    const float x = (t - center) / width;
    return amplitude * std::exp(-x * x);
}

QImage BScanWorker::toImage() const
{
    QImage image(width_, height_, QImage::Format_Grayscale8);

    for (int y = 0; y < height_; ++y) {
        uchar* row = image.scanLine(y);

        for (int x = 0; x < width_; ++x) {
            float v = buffer_[y * width_ + x];

            // нормализация (envelope)
            int gray = static_cast<int>(v * 255.0f);
            gray = std::clamp(gray, 0, 255);

            row[x] = static_cast<uchar>(gray);
        }
    }

    return image;
}
