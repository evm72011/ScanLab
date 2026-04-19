#include "scanlab/health/humidity_reader.h"

namespace scanlab::hardware {

HumidityReader::HumidityReader(Device& device)
    : device_(device)
{
}

std::expected<int, HealthError> HumidityReader::readMax() const {
    return 25;
}
}// namespace scanlab::hardware
