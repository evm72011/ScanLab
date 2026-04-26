#pragma once

#include "scanlab/acquisition/ascan_parameters.h"
#include "scanlab/acquisition/acquisition_error.h"
#include "scanlab/acquisition/acquisition_setup_snapshot.h"
#include "scanlab/device/device.h"

#include <expected>

namespace scanlab::acquisition {

class AcquisitionConfigurator {
public:
    explicit AcquisitionConfigurator(device::Device& device, AcquisitionSetupSnapshot& snapshot);

    std::expected<int, AcquisitionError> getCycleCount() const;

    std::expected<AscanParameters, AcquisitionError>
    getAscanParameters(int cycle) const;

    std::expected<void, AcquisitionError>
    setAscanParameters(const AscanParameters& parameters);

private:
    device::Device& device_;
    AcquisitionSetupSnapshot& snapshot_;
};

} // namespace scanlab::acquisition