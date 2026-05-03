#pragma once

#include <QObject>
#include <QThread>
#include <QString>
#include <QVariantList>

namespace scanlab::acquisition {
struct AscanParameters;
}

class DeviceContext;
class AcquisitionConfigurationWorker;

class AcquisitionConfigurationFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int cycleCount READ cycleCount NOTIFY cycleCountChanged)
    Q_PROPERTY(QVariantList cycles READ cycles NOTIFY cyclesChanged)
    Q_PROPERTY(int cycle READ cycle WRITE setCycle NOTIFY cycleChanged)

    Q_PROPERTY(double start READ start WRITE setStart NOTIFY startChanged)
    Q_PROPERTY(double range READ range WRITE setRange NOTIFY rangeChanged)
    Q_PROPERTY(int pointCount READ pointCount WRITE setPointCount NOTIFY pointCountChanged)

    Q_PROPERTY(bool unavailable READ unavailable NOTIFY unavailableChanged)
    Q_PROPERTY(QString errorCode READ errorCode NOTIFY errorCodeChanged)

public:
    explicit AcquisitionConfigurationFacade(DeviceContext& context, QObject* parent = nullptr);
    ~AcquisitionConfigurationFacade();

    int cycleCount() const;
    QVariantList cycles() const;
    int cycle() const;

    double start() const;
    double range() const;
    int pointCount() const;

    bool unavailable() const;
    QString errorCode() const;

public slots:
    //void refresh();
    void readCycleCount();
    void apply();

    void setCycle(int value);
    void setStart(double value);
    void setRange(double value);
    void setPointCount(int value);

signals:
    void cycleCountChanged();
    void cyclesChanged();
    void cycleChanged();

    void startChanged();
    void rangeChanged();
    void pointCountChanged();

    void unavailableChanged();
    void errorCodeChanged();

    void writeSucceeded();

    void requestReadCycleCount();
    void requestReadAscanParameters(int cycle);
    void requestWriteAscanParameters(scanlab::acquisition::AscanParameters parameters);

private:
    void setCycleCount(int value);
    void setUnavailable(bool value);
    void setErrorCode(const QString& value);

private:
    QThread workerThread_;
    AcquisitionConfigurationWorker* worker_ = nullptr;

    int cycleCount_ = 0;
    QVariantList cycles_;
    int cycle_ = 0;

    double start_ = 0.0;
    double range_ = 0.0;
    int pointCount_ = 0;

    bool unavailable_ = false;
    QString errorCode_;
};