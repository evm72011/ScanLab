#include "scanlab/hardware/health/temperature_reader.h"


namespace scanlab::hardware {

TemperatureReader::TemperatureReader(Device& device)
    : device_(device)
{
}

std::expected<int, HealthErrorCodes> TemperatureReader::readMax() const {
    return 25;
}
} // namespace scanlab::hardware