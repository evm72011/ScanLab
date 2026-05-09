#pragma once

#include <vector>
#include <string>

namespace scanlab::license {

struct Data {
    std::vector<std::string> devices;
    std::string signatureBase64;
};

} // namespace license
