#pragma once

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QImage>

class BScanWorker : public QObject
{
    Q_OBJECT

public:
    explicit BScanWorker(QObject* parent = nullptr);

public slots:
    void start();
    void stop();
    void setSize(int width, int height);

signals:
    void frameReady(const QImage& image);

private:
    void generate();
    void initializeFrame();
    void fillLine(float* line);
    QImage toImage() const;

    float pulse(float t, float center, float width, float amplitude) const;

private:
    QTimer* timer_ = nullptr;

    int width_ = 512;
    int height_ = 256;

    QVector<float> buffer_;
};
