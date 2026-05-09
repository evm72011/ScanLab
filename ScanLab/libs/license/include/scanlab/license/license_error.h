#pragma once

namespace scanlab::license
{

enum class LicenseError
{
    LicensePathNotSet,
    FileNotFound,
    InvalidJson,
    InvalidDevices,
    DevicesNotSorted,
    PublicKeyNotConfigured,
    InvalidPublicKey,
    InvalidSignature,
    DeviceNotLicensed,
    CryptoInitFailed
};

} // namespace scanlab::license
