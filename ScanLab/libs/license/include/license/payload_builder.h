#pragma once

#include <vector>
#include <string>

namespace license {

class PayloadBuilder {
public:
    static std::string buildDevicesPayload(
        const std::vector<std::string>& devices
        );
};

} // namespace license