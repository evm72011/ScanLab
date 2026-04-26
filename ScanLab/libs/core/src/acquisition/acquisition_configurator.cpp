#include "scanlab/acquisition/acquisition_configurator.h"


#include <UTDriverOEMPA.h>

namespace sd = scanlab::device;

namespace scanlab::acquisition {

AcquisitionConfigurator::AcquisitionConfigurator(
    sd::Device& device,
    AcquisitionSetupSnapshot& snapshot)
    : device_(device)
    , snapshot_(snapshot)
{
}

std::expected<int, AcquisitionError>
AcquisitionConfigurator::getCycleCount() const
{
    auto* hw = device_.get();
    if (!hw) {
        return std::unexpected(sd::HardwareError::HardwareNotSet);
    }

    if (!hw->LockDevice(eAcqContinue)) {
        return std::unexpected(sd::HardwareError::DeviceLockFailed);
    }

    int cycleCount = 0;
    const bool ok = hw->GetCycleCount(&cycleCount);

    const bool unlocked = hw->UnlockDevice(eAcqContinue);

    if (!unlocked) {
        return std::unexpected(sd::HardwareError::DeviceUnlockFailed);
    }

    if (!ok) {
        return std::unexpected(AcquisitionErrorKind::ReadParameterFailed);
    }

    return static_cast<int>(cycleCount);
}

std::expected<AscanParameters, AcquisitionError>
AcquisitionConfigurator::getAscanParameters(int cycle) const
{
    return snapshot_.getAscanParameters(cycle);
}

/*
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
*/

std::expected<void, AcquisitionError>
AcquisitionConfigurator::setAscanParameters(const AscanParameters&)
{
    auto* hw = device_.get();
    if (!hw) {
        return std::unexpected(sd::HardwareError::HardwareNotSet);
    }

    if (!hw->LockDevice()) {
        return std::unexpected(sd::HardwareError::DeviceLockFailed);
    }

    bool ok = true;

    const int cycle = 0;

    double start = 5.0e-6;       // Start=0.000000 us
    double range = 30.0e-6;      // Range=30.000000 us
    long pointCount = 3001;      // PointCount=3001
    long pointFactor = 0;

    enumCompressionType compressionType = eCompression;

    if (!hw->SetAscanStart(cycle, start)) {
        ok = false;
    }

    if (!hw->SetAscanRangeWithCount( //ok &&
            cycle,
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

    snapshot_.updateOne(AscanParameters{
        .cycle = cycle,
        .start = start,
        .range = range,
        .pointCount = static_cast<int>(pointCount),
    });

    return {};
}

} // namespace scanlab::acquisition