#pragma once

#include "scanlab/acquisition/acquisition_error.h"
#include "scanlab/acquisition/ascan/frame.h"
#include "scanlab/acquisition/ascan/pipeline.h"

#include <expected>
#include <functional>
#include <memory>
#include <mutex>

class DeviceContext;

namespace scanlab::acquisition::ascan {
class AcquisitionSource;
class RawFrame;
}

class AScanService
{
public:
    using FrameHandler = std::function<void(scanlab::acquisition::ascan::Frame&&)>;

    explicit AScanService(DeviceContext& context);
    ~AScanService();

    AScanService(const AScanService&) = delete;
    AScanService& operator=(const AScanService&) = delete;
    AScanService(AScanService&&) = delete;
    AScanService& operator=(AScanService&&) = delete;

    void setFrameHandler(FrameHandler handler);

    std::expected<void, scanlab::acquisition::AcquisitionError> start();
    void stop();
    bool isRunning() const;

    void setCropMargins(double leftFraction, double rightFraction);
    void setResampleTargetSampleCount(int value);

    void setTransformSteps(
        std::vector<scanlab::acquisition::ascan::TransformStep> steps);

private:
    void handleRawFrame(scanlab::acquisition::ascan::RawFrame&& rawFrame);

private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::acquisition::ascan::AcquisitionSource> source_;
    scanlab::acquisition::ascan::Pipeline pipeline_;

    FrameHandler handler_;
    mutable std::mutex mutex_;
};