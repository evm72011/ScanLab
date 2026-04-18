#pragma once

#include "scanlab/hardware/acquisition/acquisition_control.h"

#include <cstdint>
#include <functional>
#include <mutex>
#include <vector>

class  CStream_0x0001;
class  CSubStreamAscan_0x0103;
struct structAcqInfoEx;

namespace scanlab::hardware {

struct RawAScanFrame
{
    int dataSize = 0;
    int dataCount = 0;
    int cycle = 0;
    int bitSize = 0;
    bool sign = false;
    std::vector<std::uint8_t> data;
};

class AScanAcquisitionSource
{
public:
    using FrameHandler = std::function<void(RawAScanFrame&&)>;

    explicit AScanAcquisitionSource(Device& device);
    ~AScanAcquisitionSource();

    AScanAcquisitionSource(const AScanAcquisitionSource&) = delete;
    AScanAcquisitionSource& operator=(const AScanAcquisitionSource&) = delete;

    void setFrameHandler(FrameHandler handler);

    std::expected<void, AcquisitionError> start();
    void stop();
    bool isRunning() const;

private:
    void registerCallbacks();
    void unregisterCallbacks();

    static UINT WINAPI callback(
        void* p,
        structAcqInfoEx&,
        const CStream_0x0001*,
        const CSubStreamAscan_0x0103* hdr,
        const void* bufferMax,
        const void*,
        const void*);

    void handle(const CSubStreamAscan_0x0103* hdr, const void* buffer);

private:
    Device& device_;
    AcquisitionControl control_;

    FrameHandler handler_;
    mutable std::mutex mutex_;
};

} // namespace scanlab::hardware