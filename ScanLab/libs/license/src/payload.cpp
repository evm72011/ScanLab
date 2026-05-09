#include "scanlab/license/payload.h"

namespace scanlab::license
{

std::string Payload::fromDevices(const std::vector<std::string>& devices)
{
    std::string payload;

    for (std::size_t i = 0; i < devices.size(); ++i)
    {
        if (i > 0)
        {
            payload += '\n';
        }

        payload += devices[i];
    }

    return payload;
}

} // namespace scanlab::license