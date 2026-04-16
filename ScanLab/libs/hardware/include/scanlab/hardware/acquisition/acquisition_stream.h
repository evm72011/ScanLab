#pragma once

#include "scanlab/hardware/device/device.h"

#include <functional>
#include <mutex>

struct CStream_0x0001;
struct CSubStreamAscan_0x0103;
struct structAcqInfoEx;

namespace scanlab::hardware {

struct RawAcquisitionFrame
{
    int dataSize = 0;
    int dataCount = 0;
    int cycle = 0;
    int bitSize = 0;
    bool sign = false;
    const void* buffer = nullptr;
};

class AcquisitionStream
{
public:
    using FrameHandler = std::function<void(RawAcquisitionFrame&&)>;

    explicit AcquisitionStream(Device& device);
    ~AcquisitionStream();

    AcquisitionStream(const AcquisitionStream&) = delete;
    AcquisitionStream& operator=(const AcquisitionStream&) = delete;
    AcquisitionStream(AcquisitionStream&&) = delete;
    AcquisitionStream& operator=(AcquisitionStream&&) = delete;

    void setFrameHandler(FrameHandler handler);

    bool start();
    void stop();
    bool isRunning() const;

private:
    CHWDeviceOEMPA* native();
    const CHWDeviceOEMPA* native() const;

    void registerCallbacks();
    void unregisterCallbacks();

    static UINT WINAPI callback(
        void* p,
        structAcqInfoEx&,
        const CStream_0x0001*,
        const CSubStreamAscan_0x0103* hdr,
        const void* buffer,
        const void*,
        const void*);

    void handle(const CSubStreamAscan_0x0103* hdr, const void* buffer);

private:
    Device& device_;
    FrameHandler handler_;
    bool running_ = false;
    mutable std::mutex mutex_;
};

} // namespace scanlab::hardware