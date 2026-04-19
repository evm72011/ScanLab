#pragma once

#include "scanlab/acquisition/acquisition_error.h"
#include "scanlab/acquisition/ascan/a_scan_frame.h"
#include "scanlab/acquisition/ascan/a_scan_pipeline.h"

#include <expected>
#include <functional>
#include <mutex>

class DeviceContext;

namespace scanlab::hardware {
class AScanAcquisitionSource;
}

class AScanService
{
public:
    using FrameHandler = std::function<void(scanlab::hardware::AScanFrame&&)>;

    explicit AScanService(DeviceContext& context);
    ~AScanService();

    AScanService(const AScanService&) = delete;
    AScanService& operator=(const AScanService&) = delete;
    AScanService(AScanService&&) = delete;
    AScanService& operator=(AScanService&&) = delete;

    void setFrameHandler(FrameHandler handler);

    std::expected<void, scanlab::hardware::AcquisitionError> start();
    void stop();
    bool isRunning() const;

private:
    void handleRawFrame(scanlab::hardware::RawAScanFrame&& rawFrame);

private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::hardware::AScanAcquisitionSource> source_;
    scanlab::hardware::AScanPipeline pipeline_;

    FrameHandler handler_;
    mutable std::mutex mutex_;
};