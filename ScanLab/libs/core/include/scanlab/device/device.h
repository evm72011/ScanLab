#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <optional>
#include <filesystem>
#include <expected>
#include <UTDriverOEMPA.h>

#include "scanlab/device/device_type.h"
#include "scanlab/device/connection_error.h"
#include "scanlab/device/connection_result.h"

#include "scanlab/license/checker.h"
#include "scanlab/license/ed25519_verifier.h"

namespace scanlab::device {

class Device
{

public:
    Device(std::filesystem::path licensePath, std::string licensePublicKeyBase64);
    ~Device() = default;

    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;

    Device(Device&&) noexcept;
    Device& operator=(Device&&) noexcept;

    bool ensureDevice(DeviceType type);

    std::expected<ConnectionResult,ConnectionError> connect(const std::wstring& address);
    bool disconnect();

    bool hasDevice() const;
    bool isConnected() const;

    CHWDeviceOEMPA* get();
    const CHWDeviceOEMPA* get() const;
private:
    std::unique_ptr<CHWDeviceOEMPA> device_;
    std::optional<DeviceType> type_;
    scanlab::license::Checker<scanlab::license::Ed25519Verifier> licenseChecker_;
#ifdef MOCK_DEVICE
    bool connected_ = false;
#endif
};

} // namespace scanlab::device
