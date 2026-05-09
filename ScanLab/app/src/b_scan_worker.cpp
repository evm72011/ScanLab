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
    if (timer_ != nullptr)
    {
        return;
    }

    width_ = std::max(width_, 2);
    height_ = std::max(height_, 2);

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
    if (timer_ == nullptr)
    {
        return;
    }

    timer_->stop();
    delete timer_;
    timer_ = nullptr;
}

void BScanWorker::setSize(int width, int height)
{
    if (width < 2 || height < 2)
    {
        return;
    }

    if (width_ == width && height_ == height)
    {
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
    if (buffer_.isEmpty())
    {
        return;
    }

    phase_ += 0.04f;

    std::memmove(buffer_.data() + width_,
        buffer_.data(),
        sizeof(float) * static_cast<size_t>(width_) * static_cast<size_t>(height_ - 1));

    fillLine(buffer_.data(), 0);

    emit frameReady(toImage());
}

void BScanWorker::initializeFrame()
{
    if (buffer_.isEmpty())
    {
        return;
    }

    for (int y = 0; y < height_; ++y)
    {
        fillLine(buffer_.data() + y * width_, y);
        phase_ += 0.02f;
    }

    emit frameReady(toImage());
}

void BScanWorker::fillLine(float* line, int lineIndex)
{
    const float scanPos =
        height_ > 1 ? static_cast<float>(lineIndex) / static_cast<float>(height_ - 1) : 0.0f;

    const float entryCenter = 0.05f;

    const float defectCenter = 0.38f + 0.025f * std::sin(scanPos * 8.0f + phase_);

    const float backwallCenter = 0.82f + 0.020f * std::sin(scanPos * 5.0f + phase_ * 0.7f);

    const float defectWindow = std::exp(-std::pow((scanPos - 0.45f) / 0.16f, 2.0f));

    for (int x = 0; x < width_; ++x)
    {
        const float t = static_cast<float>(x) / static_cast<float>(width_ - 1);

        float v = 0.0f;

        // Небольшой шум
        v += 0.02f * static_cast<float>(QRandomGenerator::global()->generateDouble());

        // Entry echo
        v += 0.85f * std::exp(-std::pow((t - entryCenter) / 0.010f, 2.0f));

        // Дефект
        v += 0.55f * defectWindow * std::exp(-std::pow((t - defectCenter) / 0.014f, 2.0f));

        // Backwall
        float backwall = 0.45f * std::exp(-std::pow((t - backwallCenter) / 0.018f, 2.0f));

        // Небольшая тень от дефекта на backwall
        const float shadow =
            1.0f - 0.35f * defectWindow * std::exp(-std::pow((t - backwallCenter) / 0.035f, 2.0f));

        backwall *= std::max(shadow, 0.0f);

        v += backwall;

        // Затухание по глубине
        v *= std::exp(-0.9f * t);

        line[x] = v;
    }
}

QImage BScanWorker::toImage() const
{
    QImage image(width_, height_, QImage::Format_Grayscale8);

    for (int y = 0; y < height_; ++y)
    {
        uchar* row = image.scanLine(y);

        for (int x = 0; x < width_; ++x)
        {
            float v = buffer_[y * width_ + x];
            v = std::clamp(v, 0.0f, 1.0f);

            // Немного подсветить слабые сигналы
            v = std::sqrt(v);

            row[x] = static_cast<uchar>(v * 255.0f);
        }
    }

    return image;
}
