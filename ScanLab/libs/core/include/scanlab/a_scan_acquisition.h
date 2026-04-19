#pragma once

#include "scanlab/device/device.h"

#include <functional>
#include <memory>
#include <vector>

namespace scanlab::hardware {

class AScanAcquisition
{
public:
    struct Frame
    {
        std::vector<float> samples;
        int cycle = 0;
        int dataSize = 0;
        int bitSize = 0;
        bool sign = false;
    };

    using SamplesHandler = std::function<void(Frame)>;

    AScanAcquisition();
    ~AScanAcquisition();

    AScanAcquisition(const AScanAcquisition&) = delete;
    AScanAcquisition& operator=(const AScanAcquisition&) = delete;

    AScanAcquisition(AScanAcquisition&&) noexcept;
    AScanAcquisition& operator=(AScanAcquisition&&) noexcept;

    void setDevice(scanlab::device::Device* device);
    scanlab::device::Device* device();
    const scanlab::device::Device* device() const;

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