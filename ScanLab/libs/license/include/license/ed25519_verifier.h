#pragma once

#include <string>

#include "status.h"

namespace license {

class Ed25519Verifier {
public:
    explicit Ed25519Verifier(std::string publicKeyBase64);

    [[nodiscard]]
    bool isReady() const noexcept;

    [[nodiscard]]
    Status status() const noexcept;

    [[nodiscard]]
    bool verify(
        std::string_view payload,
        std::string_view signatureBase64
        ) const;

private:
    std::string publicKeyBase64_;
    Status status_ = Status::Valid;
};

} // namespace license
