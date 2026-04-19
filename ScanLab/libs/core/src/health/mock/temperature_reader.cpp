#include "scanlab/health/temperature_reader.h"


namespace scanlab::hardware {

TemperatureReader::TemperatureReader(Device& device)
    : device_(device)
{
}

std::expected<int, HealthError> TemperatureReader::readMax() const {
    return 20;
}
} // namespace scanlab::hardware