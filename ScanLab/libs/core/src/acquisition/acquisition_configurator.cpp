#include "scanlab/device/device_lock_guard.h"
#include "scanlab/acquisition/acquisition_configurator.h"

#include <UTDriverOEMPA.h>

namespace sd = scanlab::device;

namespace scanlab::acquisition {

AcquisitionConfigurator::AcquisitionConfigurator(sd::Device& device)
    : device_(device)
{
}

std::expected<int, AcquisitionError>
AcquisitionConfigurator::getCycleCount() const
{
    auto* hw = device_.get();
    if (!hw) {
        return std::unexpected(sd::HardwareError::HardwareNotSet);
    }

    if (!hw->LockDevice()) {
        return std::unexpected(sd::HardwareError::DeviceLockFailed);
    }

    int cycleCount = 0;
    const bool ok = hw->GetCycleCount(&cycleCount);

    const bool unlocked = hw->UnlockDevice();

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
    auto* hw = device_.get();
    if (!hw) {
        return std::unexpected(sd::HardwareError::HardwareNotSet);
    }

    DeviceLockGuard lock(*hw);
    if (!lock.locked()) {
        return std::unexpected(sd::HardwareError::DeviceLockFailed);
    }

    AscanParameters parameters;
    parameters.cycle = cycle;

    enumCompressionType compressionType {};
    long pointFactor = 0;
    long pointCount = 0;

    if (!hw->GetAscanStart(cycle, &parameters.start)) {
        return std::unexpected(AcquisitionErrorKind::ReadParameterFailed);
    }

    if (!hw->GetAscanRange(
            cycle,
            &parameters.range,
            &compressionType,
            &pointFactor,
            &pointCount)) {
        return std::unexpected(AcquisitionErrorKind::ReadParameterFailed);
    }

    parameters.pointCount = static_cast<int>(pointCount);

    if (!lock.release()) {
        return std::unexpected(sd::HardwareError::DeviceUnlockFailed);
    }

    return parameters;
}

std::expected<AscanParameters, AcquisitionError>
AcquisitionConfigurator::getAscanParameters_(int cycle) const
{
    auto* hw = device_.get();  // hw is CHWDeviceOEMPA* here
    if (!hw) {
        return std::unexpected(sd::HardwareError::HardwareNotSet);
    }



    if (!hw->LockDevice()) {
        return std::unexpected(sd::HardwareError::DeviceLockFailed);
    }

    AscanParameters parameters;
    parameters.cycle = cycle;
    /*
    struct AscanParameters {
        int cycle = 0;
        double start = 0.0;
        double range = 0.0;
        int pointCount = 0;
    };
    */

    enumCompressionType compressionType {};
    long pointFactor = 0;
    long pointCount = 0;
    //double dGain = 5.55;

    bool ok = true; // hw->GetGainDigital(cycle, &dGain); - works fine

    // as GetAscanStart as GetAscanRange return false - why ???
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

    DeviceLockGuard lock(*hw);

    if (!lock.locked()) {
        return std::unexpected(sd::HardwareError::DeviceLockFailed);
    }

    double start = parameters.start;
    double range = parameters.range;
    long pointCount = static_cast<long>(parameters.pointCount);
    long pointFactor = 0;

    // Better than SetAscanRange() here, because PointCount is explicit.
    enumCompressionType compressionType = eCompression;

    if (!hw->SetAscanStart(parameters.cycle, start)) {
         return std::unexpected(AcquisitionErrorKind::WriteParameterFailed);
    }

    if (!hw->SetAscanRangeWithCount(
            parameters.cycle,
            range,
            compressionType,
            pointCount,
            pointFactor)) {
        return std::unexpected(AcquisitionErrorKind::WriteParameterFailed);
    }

    if (!lock.release()) {
        return std::unexpected(sd::HardwareError::DeviceUnlockFailed);
    }

    return {};
}

} // namespace scanlab::acquisition