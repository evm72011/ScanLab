#include "scanlab/acquisition/ascan/a_scan_raw_decoder.h"

#include <algorithm>
#include <limits>

namespace scanlab::acquisition::ascan {

std::vector<float> AScanRawDecoder::decode(const RawAScanFrame& frame) const
{
    if (frame.data.empty()) {
        return {};
    }

    return decodeBuffer(
        frame.data.data(),
        frame.dataSize,
        frame.dataCount,
        frame.bitSize,
        frame.sign);
}

int AScanRawDecoder::effectiveBitWidth(int bitSize, int dataSize)
{
    switch (bitSize) {
    case eLog8Bits:
    case e8Bits:
        return 8;

    case e12Bits:
        if (dataSize == 4) {
            return 27; // OEMPA special packed format
        }
        if (dataSize == 2) {
            return 16;
        }
        return 12;

    case e16Bits:
        return 16;

#ifdef MC2_FULL_DYNAMIC
    case e30Bits:
        return 30;
#endif

    default:
        return dataSize * 8;
    }
}

float AScanRawDecoder::normalizeSigned(std::int64_t value, int bits)
{
    if (bits <= 1) {
        return 0.0f;
    }

    const std::int64_t maxPositive = (std::int64_t{1} << (bits - 1)) - 1;

    if (maxPositive <= 0) {
        return 0.0f;
    }

    double v = static_cast<double>(value) / static_cast<double>(maxPositive);
    v = std::clamp(v, -1.0, 1.0);

    return static_cast<float>(v);
}

float AScanRawDecoder::normalizeUnsigned(std::uint64_t value, int bits)
{
    if (bits <= 0) {
        return 0.0f;
    }

    const std::uint64_t maxValue =
        (bits >= 64)
            ? std::numeric_limits<std::uint64_t>::max()
            : ((std::uint64_t{1} << bits) - 1);

    if (maxValue == 0) {
        return 0.0f;
    }

    double v = static_cast<double>(value) / static_cast<double>(maxValue);
    v = std::clamp(v, 0.0, 1.0);

    return static_cast<float>(v);
}

std::vector<float> AScanRawDecoder::decodeBuffer(
    const std::uint8_t* data,
    int dataSize,
    int dataCount,
    int bitSize,
    bool sign)
{
    std::vector<float> result;

    if (!data || dataSize <= 0 || dataCount <= 0) {
        return result;
    }

    result.reserve(static_cast<std::size_t>(dataCount));

    const int bits = effectiveBitWidth(bitSize, dataSize);

    switch (dataSize) {

    case 1:
        if (sign) {
            const auto* src = reinterpret_cast<const std::int8_t*>(data);
            for (int i = 0; i < dataCount; ++i) {
                result.push_back(normalizeSigned(src[i], 8));
            }
        } else {
            const auto* src = reinterpret_cast<const std::uint8_t*>(data);
            for (int i = 0; i < dataCount; ++i) {
                result.push_back(normalizeUnsigned(src[i], 8));
            }
        }
        break;

    case 2:
        if (sign) {
            const auto* src = reinterpret_cast<const std::int16_t*>(data);
            for (int i = 0; i < dataCount; ++i) {
                result.push_back(normalizeSigned(src[i], bits));
            }
        } else {
            const auto* src = reinterpret_cast<const std::uint16_t*>(data);
            for (int i = 0; i < dataCount; ++i) {
                result.push_back(normalizeUnsigned(src[i], bits));
            }
        }
        break;

    case 4:
        if (sign) {
            const auto* src = reinterpret_cast<const std::int32_t*>(data);
            for (int i = 0; i < dataCount; ++i) {
                result.push_back(normalizeSigned(src[i], bits));
            }
        } else {
            const auto* src = reinterpret_cast<const std::uint32_t*>(data);
            for (int i = 0; i < dataCount; ++i) {
                result.push_back(normalizeUnsigned(src[i], bits));
            }
        }
        break;

    default:
        break;
    }

    return result;
}

} // namespace scanlab::acquisition::ascan