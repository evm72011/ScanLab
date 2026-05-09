#pragma once

#include <vector>
#include <string>

namespace scanlab::license {

class Payload {
public:
    [[nodiscard]]
    static std::string fromDevices(const std::vector<std::string>& devices);
};

} // namespace license
