#pragma once

namespace scanlab::license {

enum class LicenseError {
    LicensePathNotSet,
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
