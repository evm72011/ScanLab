#include "scanlab/acquisition/acquisition_setup_snapshot.h"

#include <cstddef>

namespace scanlab::acquisition {

void AcquisitionSetupSnapshot::update(
    int cycleCount,
    double digitizingPeriod,
    const std::vector<AscanParameters>& parameters)
{
    std::lock_guard lock(mutex_);

    cycleCount_ = cycleCount;
    digitizingPeriod_ = digitizingPeriod;
    parameters_ = parameters;
    valid_ = true;
}

void AcquisitionSetupSnapshot::updateOne(const AscanParameters& parameters)
{
    std::lock_guard lock(mutex_);

    if (parameters.cycle < 0) {
        return;
    }

    const auto index = static_cast<std::size_t>(parameters.cycle);

    if (index >= parameters_.size()) {
        parameters_.resize(index + 1);
    }

    parameters_[index] = parameters;

    if (cycleCount_ <= parameters.cycle) {
        cycleCount_ = parameters.cycle + 1;
    }

    valid_ = true;
}

std::expected<int, AcquisitionError>
AcquisitionSetupSnapshot::getCycleCount() const
{
    std::lock_guard lock(mutex_);

    if (!valid_) {
        return std::unexpected(AcquisitionErrorKind::ReadParameterFailed);
    }

    return cycleCount_;
}

std::expected<AscanParameters, AcquisitionError>
AcquisitionSetupSnapshot::getAscanParameters(int cycle) const
{
    std::lock_guard lock(mutex_);

    if (!valid_ || cycle < 0 ||
        cycle >= static_cast<int>(parameters_.size())) {
        return std::unexpected(AcquisitionErrorKind::ReadParameterFailed);
    }

    return parameters_[static_cast<std::size_t>(cycle)];
}

} // namespace scanlab::acquisition