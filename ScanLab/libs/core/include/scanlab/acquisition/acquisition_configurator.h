#pragma once

#include "scanlab/acquisition/acquisition_error.h"
#include "scanlab/acquisition/ascan_parameters.h"
#include "scanlab/device/device.h"

#include <expected>

namespace scanlab::acquisition
{

class AcquisitionConfigurator
{
public:
    explicit AcquisitionConfigurator(device::Device& device);

    std::expected<int, AcquisitionError> getCycleCount() const;

    std::expected<AscanParameters, AcquisitionError> getAscanParameters(int cycle) const;
    std::expected<AscanParameters, AcquisitionError> getAscanParameters_(int cycle) const;

    std::expected<void, AcquisitionError> setAscanParameters(const AscanParameters& parameters);

private:
    device::Device& device_;
};

} // namespace scanlab::acquisition