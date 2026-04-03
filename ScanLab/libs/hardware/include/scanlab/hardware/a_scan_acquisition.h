#pragma once

#include "scanlab/hardware/device.h"

#include <functional>
#include <memory>
#include <vector>

namespace scanlab::hardware {

class AScanAcquisition
{
public:
    using Samples = std::vector<float>;
    using SamplesHandler = std::function<void(Samples)>;

    AScanAcquisition();
    ~AScanAcquisition();

    AScanAcquisition(const AScanAcquisition&) = delete;
    AScanAcquisition& operator=(const AScanAcquisition&) = delete;

    AScanAcquisition(AScanAcquisition&&) noexcept;
    AScanAcquisition& operator=(AScanAcquisition&&) noexcept;

    void setDevice(Device* device);
    Device* device();
    const Device* device() const;

    void setSamplesHandler(SamplesHandler handler);
    void setTargetSampleCount(int value);

    bool start();
    void stop();
    bool isRunning() const;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace scanlab::hardware