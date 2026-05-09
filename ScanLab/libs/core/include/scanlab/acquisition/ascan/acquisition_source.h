#pragma once

#include "scanlab/acquisition/acquisition_control.h"

#include <cstdint>
#include <functional>
#include <mutex>
#include <vector>

class CStream_0x0001;
class CSubStreamAscan_0x0103;
struct structAcqInfoEx;

namespace scanlab::acquisition::ascan
{

struct RawFrame
{
    int dataSize = 0;
    int dataCount = 0;
    int cycle = 0;
    int bitSize = 0;
    bool sign = false;
    std::vector<std::uint8_t> data;
};

class AcquisitionSource
{
public:
    using FrameHandler = std::function<void(RawFrame &&)>;

    explicit AcquisitionSource(scanlab::device::Device &device);
    ~AcquisitionSource();

    AcquisitionSource(const AcquisitionSource &) = delete;
    AcquisitionSource &operator=(const AcquisitionSource &) = delete;

    void setFrameHandler(FrameHandler handler);
    void setCycleFilter(int cycle);
    void clearCycleFilter();

    std::expected<void, AcquisitionError> start();
    void stop();
    bool isRunning() const;

private:
    void registerCallbacks();
    void unregisterCallbacks();

    static UINT WINAPI callback(void *p,
                                structAcqInfoEx &,
                                const CStream_0x0001 *,
                                const CSubStreamAscan_0x0103 *hdr,
                                const void *bufferMax,
                                const void *,
                                const void *);

    void handle(const CSubStreamAscan_0x0103 *hdr, const void *buffer);

private:
    scanlab::device::Device &device_;
    AcquisitionControl control_;

    std::optional<int> cycleFilter_{0};

    FrameHandler handler_;
    mutable std::mutex mutex_;
};

} // namespace scanlab::acquisition::ascan