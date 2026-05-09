#pragma once

namespace license {

enum class Status {
    Valid,
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
