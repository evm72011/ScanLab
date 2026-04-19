#pragma once

#include "scanlab/acquisition/ascan/acquisition_source.h"

#include <cstdint>
#include <vector>

namespace scanlab::acquisition::ascan {

class RawDecoder
{
public:
    std::vector<float> decode(const RawFrame& frame) const;

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

} // namespace scanlab::acquisition::ascan