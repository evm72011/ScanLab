#pragma once

#include "scanlab/hardware/acquisition/ascan/a_scan_acquisition_source.h"

#include <cstdint>
#include <vector>

namespace scanlab::hardware {

class AScanRawDecoder
{
public:
    std::vector<float> decode(const RawAScanFrame& frame) const;

private:
    static int effectiveBitWidth(int bitSize, int dataSize);

    static float normalizeSigned(std::int64_t value, int bits);
    static float normalizeUnsigned(std::uint64_t value, int bits);

    static std::vector<float> decodeBuffer(
        const std::uint8_t* data,
        int dataSize,
        int dataCount,
        int bitSize,
        bool sign);
};

} // namespace scanlab::hardware