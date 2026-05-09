#pragma once

#include <QImage>
#include <QObject>
#include <QTimer>
#include <QVector>

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
    void fillLine(float* line, int lineIndex);
    QImage toImage() const;

private:
    QTimer* timer_ = nullptr;

    int width_ = 512;
    int height_ = 256;

    QVector<float> buffer_;
    float phase_ = 0.0f;
};
