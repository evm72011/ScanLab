#include <nlohmann/json.hpp>
#include <sodium.h>

#include "license/ed25519_verifier.h"

namespace license {

namespace {

bool decodeBase64(
    std::string_view input,
    unsigned char* output,
    std::size_t outputSize,
    std::size_t expectedSize
    ) {
    std::size_t actualSize = 0;

    const auto result = sodium_base642bin(
        output,
        outputSize,
        input.data(),
        input.size(),
        nullptr,
        &actualSize,
        nullptr,
        sodium_base64_VARIANT_ORIGINAL
        );

    return result == 0 && actualSize == expectedSize;
}
} // namespace

Ed25519Verifier::Ed25519Verifier(std::string publicKeyBase64)
    : publicKeyBase64_(std::move(publicKeyBase64)) {
    if (sodium_init() < 0) {
        status_ = Status::CryptoInitFailed;
        return;
    }

    unsigned char publicKey[crypto_sign_PUBLICKEYBYTES];

    if (!decodeBase64(
            publicKeyBase64_,
            publicKey,
            sizeof(publicKey),
            crypto_sign_PUBLICKEYBYTES
        )) {
        status_ = Status::InvalidPublicKey;
        return;
    }

    status_ = Status::Valid;
}

bool Ed25519Verifier::isReady() const noexcept {
    return status_ == Status::Valid;
}

Status Ed25519Verifier::status() const noexcept {
    return status_;
}

bool Ed25519Verifier::verify(
    std::string_view payload,
    std::string_view signatureBase64
) const {
    unsigned char publicKey[crypto_sign_PUBLICKEYBYTES];
    unsigned char signature[crypto_sign_BYTES];

    if (!decodeBase64(
            publicKeyBase64_,
            publicKey,
            sizeof(publicKey),
            crypto_sign_PUBLICKEYBYTES
        )) {
        return false;
    }

    if (!decodeBase64(
            signatureBase64,
            signature,
            sizeof(signature),
            crypto_sign_BYTES
        )) {
        return false;
    }

    const auto result = crypto_sign_verify_detached(
        signature,
        reinterpret_cast<const unsigned char*>(payload.data()),
        payload.size(),
        publicKey
    );

    return result == 0;
}
}