#pragma once

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QVariantList>
#include <QString>
#include <qqmlintegration.h>

class DeviceContext;
class TemperatureWorker;

class TemperatureFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int maxTemperature READ maxTemperature NOTIFY maxTemperatureChanged)
    Q_PROPERTY(bool maxTemperatureUnavailable READ maxTemperatureUnavailable NOTIFY maxTemperatureUnavailableChanged)
    Q_PROPERTY(QString maxTemperatureErrorCode READ maxTemperatureErrorCode NOTIFY maxTemperatureErrorCodeChanged)

public:
    explicit TemperatureFacade(DeviceContext& context, QObject* parent = nullptr);
    ~TemperatureFacade() override;

    bool maxTemperatureUnavailable() const;
    int maxTemperature() const;
    QString maxTemperatureErrorCode() const;

    Q_INVOKABLE void startMaxTemperaturePolling();
    Q_INVOKABLE void stopMaxTemperaturePolling();

signals:
    void requestPollMaxTemperature();
    void maxTemperatureUnavailableChanged();
    void maxTemperatureChanged();
    void maxTemperatureErrorCodeChanged();

private:
    void pollMaxTemperature();
    void setMaxTemperature(int value);
    void setMaxTemperatureUnavailable(bool value);
    void setMaxTemperatureErrorCode(const QString& value);

private:
    QTimer timer_;
    int interval_ = 60'000;

    int maxTemperature_ = 0;
    bool maxTemperatureUnavailable_ = true;
    QString maxTemperatureErrorCode_;

    TemperatureWorker* worker_ = nullptr;
    QThread workerThread_;
};