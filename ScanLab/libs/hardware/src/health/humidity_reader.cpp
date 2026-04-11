#include "scanlab/hardware/health/humidity_reader.h"

namespace scanlab::hardware {

HumidityReader::HumidityReader(Device& device)
    : device_(device)
{
}

}// namespace scanlab::hardware
