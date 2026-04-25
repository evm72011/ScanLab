#pragma once

#include "scanlab/acquisition/acquisition_error.h"
#include "scanlab/acquisition/ascan/frame.h"
#include "scanlab/acquisition/ascan/pipeline.h"
#include "scanlab/acquisition/ascan/cropper.h"

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
    void setEnvelopeTargetPointCount(int value);
private:
    void handleRawFrame(scanlab::acquisition::ascan::RawFrame&& rawFrame);

private:
    DeviceContext& context_;
    std::unique_ptr<scanlab::acquisition::ascan::AcquisitionSource> source_;
    std::shared_ptr<scanlab::acquisition::ascan::Cropper> cropper_;

    scanlab::acquisition::ascan::Pipeline pipeline_;

    FrameHandler handler_;
    mutable std::mutex mutex_;
};