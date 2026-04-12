#pragma once

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QVariantList>
#include <QString>
#include <qqmlintegration.h>

class DeviceContext;
class HumidityWorker;

class HumidityFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int maxHumidity READ maxHumidity NOTIFY maxHumidityChanged)
    Q_PROPERTY(bool maxHumidityUnavailable READ maxHumidityUnavailable NOTIFY maxHumidityUnavailableChanged)
    Q_PROPERTY(QString maxHumidityErrorCode READ maxHumidityErrorCode NOTIFY maxHumidityErrorCodeChanged)

public:
    explicit HumidityFacade(DeviceContext& context, QObject* parent = nullptr);
    ~HumidityFacade() override;

    bool maxHumidityUnavailable() const;
    int maxHumidity() const;
    QString maxHumidityErrorCode() const;

    Q_INVOKABLE void startMaxHumidityPolling();
    Q_INVOKABLE void stopMaxHumidityPolling();

signals:
    void requestPollMaxHumidity();
    void maxHumidityUnavailableChanged();
    void maxHumidityChanged();
    void maxHumidityErrorCodeChanged();

private:
    void pollMaxHumidity();
    void setMaxHumidity(int value);
    void setMaxHumidityUnavailable(bool value);
    void setMaxHumidityErrorCode(const QString& value);

private:
    QTimer timer_;
    int interval_ = 60'000;

    int maxHumidity_ = 0;
    bool maxHumidityUnavailable_ = true;
    QString maxHumidityErrorCode_;

    HumidityWorker* worker_ = nullptr;
    QThread workerThread_;
};