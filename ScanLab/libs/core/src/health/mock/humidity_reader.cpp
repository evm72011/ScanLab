#include "scanlab/health/humidity_reader.h"

namespace scanlab::health {

HumidityReader::HumidityReader(scanlab::device::Device& device)
    : device_(device)
{
}

std::expected<int, HealthError> HumidityReader::readMax() const {
    return 25;
}
}// namespace scanlab::health
