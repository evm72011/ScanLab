#pragma once

#include "scanlab/acquisition/acquisition_configurator.h"
#include "scanlab/acquisition/ascan_parameters.h"

class DeviceContext;

class AcquisitionConfigurationService {
public:
    explicit AcquisitionConfigurationService(DeviceContext& context);
    ~AcquisitionConfigurationService();

    std::expected<int, scanlab::acquisition::AcquisitionError>
    readCycleCount() const;

    std::expected<scanlab::acquisition::AscanParameters,
                  scanlab::acquisition::AcquisitionError>
    readAscanParameters(int cycle) const;

    std::expected<void, scanlab::acquisition::AcquisitionError>
    writeAscanParameters(const scanlab::acquisition::AscanParameters& parameters);

private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::acquisition::AcquisitionConfigurator> configurator_;
};
