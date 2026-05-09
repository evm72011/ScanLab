#pragma once

#include <expected>
#include <string>
#include <string_view>

#include "scanlab/license/license_error.h"

namespace scanlab::license
{

class Ed25519Verifier
{
public:
    explicit Ed25519Verifier(std::string publicKeyBase64);

    [[nodiscard]]
    std::expected<void, LicenseError> verify(std::string_view payload,
        std::string_view signatureBase64) const;

private:
    std::string publicKeyBase64_;
    std::expected<void, LicenseError> initResult_;
};

} // namespace scanlab::license
