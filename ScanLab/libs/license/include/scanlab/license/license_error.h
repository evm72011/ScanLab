#pragma once

namespace scanlab::license {

enum class LicenseError {
    FileNotFound,
    InvalidJson,
    InvalidDevices,
    DevicesNotSorted,
    InvalidPublicKey,
    InvalidSignature,
    DeviceNotLicensed,
    CryptoInitFailed
};

} // namespace license
