#pragma once

#include "scanlab/acquisition/acquisition_error.h"
#include "scanlab/acquisition/ascan_parameters.h"

#include <expected>
#include <mutex>
#include <vector>

namespace scanlab::acquisition {

class AcquisitionSetupSnapshot {
public:
    void update(
        int cycleCount,
        double digitizingPeriod,
        const std::vector<AscanParameters>& parameters);

    void updateOne(const AscanParameters& parameters);

    std::expected<int, AcquisitionError> getCycleCount() const;

    std::expected<AscanParameters, AcquisitionError>
    getAscanParameters(int cycle) const;

private:
    mutable std::mutex mutex_;
    bool valid_ = false;
    int cycleCount_ = 0;
    double digitizingPeriod_ = 0.0;
    std::vector<AscanParameters> parameters_;
};

} // namespace scanlab::acquisition