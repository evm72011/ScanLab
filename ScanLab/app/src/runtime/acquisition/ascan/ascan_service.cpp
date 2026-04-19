#include "runtime/acquisition/ascan/ascan_service.h"

#include "runtime/device/device_context.h"

#include "scanlab/acquisition/ascan/a_scan_acquisition_source.h"
#include "scanlab/acquisition/ascan/a_scan_pipeline.h"

#include <utility>

AScanService::AScanService(DeviceContext& context)
    : context_(context)
    , source_(std::make_unique<scanlab::hardware::AScanAcquisitionSource>(*context.device()))
{
    source_->setFrameHandler([this](scanlab::hardware::RawAScanFrame&& rawFrame) {
        handleRawFrame(std::move(rawFrame));
    });
}

AScanService::~AScanService()
{
    stop();
}

void AScanService::setFrameHandler(FrameHandler handler)
{
    std::lock_guard lock(mutex_);
    handler_ = std::move(handler);
}

std::expected<void, scanlab::hardware::AcquisitionError> AScanService::start()
{
    auto* device = context_.device();
    if (!device) {
        return std::unexpected(
            scanlab::hardware::AcquisitionError {
                scanlab::device::HardwareError::HardwareNotSet
            });
    }

    if (!source_) {
        source_ = std::make_unique<scanlab::hardware::AScanAcquisitionSource>(*device);

        source_->setFrameHandler([this](scanlab::hardware::RawAScanFrame&& rawFrame) {
            handleRawFrame(std::move(rawFrame));
        });
    }

    return source_->start();
}

void AScanService::stop()
{
    source_->stop();
}

bool AScanService::isRunning() const
{
    return source_->isRunning();
}

void AScanService::handleRawFrame(scanlab::hardware::RawAScanFrame&& rawFrame)
{
    auto frame = pipeline_.process(rawFrame);

    FrameHandler localHandler;
    {
        std::lock_guard lock(mutex_);
        localHandler = handler_;
    }

    if (!localHandler) {
        return;
    }

    localHandler(std::move(frame));
}