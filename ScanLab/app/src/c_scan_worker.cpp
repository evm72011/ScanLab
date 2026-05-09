#include "c_scan_worker.h"

#include <QRandomGenerator>

#include <algorithm>
#include <cmath>

CScanWorker::CScanWorker(QObject* parent)
    : QObject(parent)
{
}

void CScanWorker::start()
{
    if (timer_ != nullptr)
    {
        return;
    }

    width_ = std::max(width_, 2);
    height_ = std::max(height_, 2);

    buffer_.resize(width_ * height_);
    buffer_.fill(0.0f);

    generate();

    timer_ = new QTimer(this);
    timer_->setInterval(80);

    connect(timer_, &QTimer::timeout, this, &CScanWorker::generate);
    timer_->start();
}

void CScanWorker::stop()
{
    if (timer_ == nullptr)
    {
        return;
    }

    timer_->stop();
    delete timer_;
    timer_ = nullptr;
}

void CScanWorker::setSize(int width, int height)
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

    generate();
}

void CScanWorker::generate()
{
    if (buffer_.isEmpty())
    {
        return;
    }

    phase_ += 0.03f;

    const float d1x = 0.32f + 0.03f * std::sin(phase_);
    const float d1y = 0.42f + 0.02f * std::cos(phase_ * 0.8f);

    const float d2x = 0.68f + 0.02f * std::cos(phase_ * 0.7f);
    const float d2y = 0.60f + 0.03f * std::sin(phase_ * 0.9f);

    for (int y = 0; y < height_; ++y)
    {
        const float ny =
            height_ > 1 ? static_cast<float>(y) / static_cast<float>(height_ - 1) : 0.0f;

        for (int x = 0; x < width_; ++x)
        {
            const float nx =
                width_ > 1 ? static_cast<float>(x) / static_cast<float>(width_ - 1) : 0.0f;

            float v = 0.03f * static_cast<float>(QRandomGenerator::global()->generateDouble());

            // Defekt 1
            v += 0.75f * std::exp(-(std::pow((nx - d1x) / 0.07f, 2.0f) +
                                    std::pow((ny - d1y) / 0.10f, 2.0f)));

            // Defekt 2
            v += 0.55f * std::exp(-(std::pow((nx - d2x) / 0.10f, 2.0f) +
                                    std::pow((ny - d2y) / 0.06f, 2.0f)));

            // Slabaja neodnorodnost'
            v += 0.08f * std::exp(-(std::pow((nx - 0.50f) / 0.25f, 2.0f) +
                                    std::pow((ny - 0.50f) / 0.18f, 2.0f)));

            buffer_[y * width_ + x] = std::clamp(v, 0.0f, 1.0f);
        }
    }

    emit frameReady(toImage());
}

QImage CScanWorker::toImage() const
{
    QImage image(width_, height_, QImage::Format_RGB32);

    auto colorMap = [](float v) -> QRgb {
        v = std::clamp(v, 0.0f, 1.0f);

        float r = std::clamp(1.5f - std::fabs(4.0f * v - 3.0f), 0.0f, 1.0f);
        float g = std::clamp(1.5f - std::fabs(4.0f * v - 2.0f), 0.0f, 1.0f);
        float b = std::clamp(1.5f - std::fabs(4.0f * v - 1.0f), 0.0f, 1.0f);

        return qRgb(static_cast<int>(r * 255),
            static_cast<int>(g * 255),
            static_cast<int>(b * 255));
    };

    for (int y = 0; y < height_; ++y)
    {
        QRgb* row = reinterpret_cast<QRgb*>(image.scanLine(y));

        for (int x = 0; x < width_; ++x)
        {
            float v = buffer_[y * width_ + x];

            // немного усилить слабые сигналы
            v = std::sqrt(std::clamp(v, 0.0f, 1.0f));

            row[x] = colorMap(v);
        }
    }

    return image;
}
