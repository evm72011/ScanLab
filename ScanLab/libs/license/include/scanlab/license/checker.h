#pragma once

#include <expected>
#include <filesystem>

#include "scanlab/license/ed25519_verifier.h"
#include "scanlab/license/license_error.h"
#include "scanlab/license/reader.h"

namespace scanlab::license
{

class Checker
{
public:
    explicit Checker(std::filesystem::path path, std::string licensePublicKeyBase64);

    [[nodiscard]]
    std::expected<void, LicenseError> check(std::string_view serialNumber) const;

private:
    Reader reader_;
    Ed25519Verifier verifier_;
};

} // namespace scanlab::license