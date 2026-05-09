#include "scanlab/health/temperature_reader.h"


namespace scanlab::health
{

TemperatureReader::TemperatureReader(scanlab::device::Device &device)
    : device_(device)
{
}

std::expected<int, HealthError> TemperatureReader::readMax() const
{
    return 20;
}
} // namespace scanlab::health