#include "scanlab/acquisition/acquisition_configurator.h"

#include <UTDriverOEMPA.h>

namespace sd = scanlab::device;

namespace scanlab::acquisition {

AcquisitionConfigurator::AcquisitionConfigurator(sd::Device& device)
    : device_(device)
{
}

std::expected<AscanParameters, AcquisitionError>
AcquisitionConfigurator::getAscanParameters(int cycle) const
{
    auto* hw = device_.get();
    if (!hw) {
        return std::unexpected(sd::HardwareError::HardwareNotSet);
    }

    if (!hw->LockDevice()) {
        return std::unexpected(sd::HardwareError::DeviceLockFailed);
    }

    AscanParameters parameters;
    parameters.cycle = cycle;

    enumCompressionType compressionType {};
    long pointFactor = 0;
    long pointCount = 0;

    bool ok = true;

    // OEMPA API uses seconds internally; OEMPA file displays us.
    if (!hw->GetAscanStart(cycle, &parameters.start)) {
        ok = false;
    }

    if (ok && !hw->GetAscanRange(
                  cycle,
                  &parameters.range,
                  &compressionType,
                  &pointFactor,
                  &pointCount)) {
        ok = false;
    }

    parameters.pointCount = static_cast<int>(pointCount);

    const bool unlocked = hw->UnlockDevice();

    if (!unlocked) {
        return std::unexpected(sd::HardwareError::DeviceUnlockFailed);
    }

    if (!ok) {
        return std::unexpected(AcquisitionErrorKind::ReadParameterFailed);
    }

    return parameters;
}

std::expected<void, AcquisitionError>
AcquisitionConfigurator::setAscanParameters(const AscanParameters& parameters)
{
    auto* hw = device_.get();
    if (!hw) {
        return std::unexpected(sd::HardwareError::HardwareNotSet);
    }

    if (!hw->LockDevice()) {
        return std::unexpected(sd::HardwareError::DeviceLockFailed);
    }

    bool ok = true;

    double start = parameters.start;
    double range = parameters.range;
    long pointCount = static_cast<long>(parameters.pointCount);
    long pointFactor = 0;

    // Better than SetAscanRange() here, because PointCount is explicit.
    enumCompressionType compressionType = eCompression;

    if (!hw->SetAscanStart(parameters.cycle, start)) {
        ok = false;
    }

    if (ok && !hw->SetAscanRangeWithCount(
                  parameters.cycle,
                  range,
                  compressionType,
                  pointCount,
                  pointFactor)) {
        ok = false;
    }

    const bool unlocked = hw->UnlockDevice();

    if (!unlocked) {
        return std::unexpected(sd::HardwareError::DeviceUnlockFailed);
    }

    if (!ok) {
        return std::unexpected(AcquisitionErrorKind::WriteParameterFailed);
    }

    return {};
}

} // namespace scanlab::acquisition