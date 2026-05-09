#pragma once

#include <string>
#include <vector>

namespace scanlab::license
{

struct Data
{
    std::vector<std::string> devices;
    std::string signatureBase64;
};

} // namespace scanlab::license
