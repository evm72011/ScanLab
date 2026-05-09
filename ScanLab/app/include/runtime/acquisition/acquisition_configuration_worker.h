#pragma once

#include <QObject>
#include <QString>

#include "runtime/acquisition/acquisition_configuration_service.h"
#include "scanlab/acquisition/ascan_parameters.h"

class DeviceContext;

class AcquisitionConfigurationWorker : public QObject
{
    Q_OBJECT

public:
    explicit AcquisitionConfigurationWorker(DeviceContext& context, QObject* parent = nullptr);

public slots:
    void readCycleCount();
    void readAscanParameters(int cycle);
    void writeAscanParameters(scanlab::acquisition::AscanParameters parameters);

signals:
    void cycleCountUpdated(int value);
    void ascanParametersUpdated(scanlab::acquisition::AscanParameters parameters);

    void writeCompleted();

    void acquisitionConfigurationUnavailable();
    void acquisitionConfigurationErrorCode(const QString& value);

private:
    AcquisitionConfigurationService service_;
};