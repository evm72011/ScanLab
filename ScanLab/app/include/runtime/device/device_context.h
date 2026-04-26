#pragma once

#include <memory>
#include "scanlab/acquisition/acquisition_setup_snapshot.h"

namespace scanlab::device {
class Device;
}

class DeviceContext
{
public:
    DeviceContext();

    DeviceContext(const DeviceContext&) = delete;
    DeviceContext& operator=(const DeviceContext&) = delete;

    ~DeviceContext();

    scanlab::device::Device* device();
    const scanlab::device::Device* device() const;

    scanlab::acquisition::AcquisitionSetupSnapshot& setupSnapshot();

private:
    std::unique_ptr<scanlab::device::Device> device_;
    scanlab::acquisition::AcquisitionSetupSnapshot setupSnapshot_;
};
