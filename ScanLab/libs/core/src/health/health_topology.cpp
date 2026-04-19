#include "scanlab/health/health_topology.h"

namespace scanlab::health {

void HealthTopology::reset() noexcept {
    hw_ = nullptr;
    boardCount_ = 0;
    sensorCountPerBoard_.clear();
    totalSensorCount_ = 0;
}

int HealthTopology::boardCount() const noexcept {
    return boardCount_;
}

std::span<const int> HealthTopology::sensorCountPerBoard() const noexcept {
    return sensorCountPerBoard_;
}

std::size_t HealthTopology::totalSensorCount() const noexcept {
    return totalSensorCount_;
}
}// namespace scanlab::health