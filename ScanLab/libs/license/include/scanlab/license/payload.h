#pragma once

#include <string>
#include <vector>

namespace scanlab::license
{

class Payload
{
public:
    [[nodiscard]]
    static std::string fromDevices(const std::vector<std::string> &devices);
};

} // namespace scanlab::license
