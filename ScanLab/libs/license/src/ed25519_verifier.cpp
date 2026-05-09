#include "scanlab/license/ed25519_verifier.h"

#include <sodium.h>

#include <utility>

namespace scanlab::license {

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

std::expected<void, LicenseError> validatePublicKey(
    std::string_view publicKeyBase64
    ) {
    if (sodium_init() < 0) {
        return std::unexpected(LicenseError::CryptoInitFailed);
    }

    unsigned char publicKey[crypto_sign_PUBLICKEYBYTES];

    if (!decodeBase64(
            publicKeyBase64,
            publicKey,
            sizeof(publicKey),
            crypto_sign_PUBLICKEYBYTES
            )) {
        return std::unexpected(LicenseError::InvalidPublicKey);
    }

    return {};
}

} // namespace

Ed25519Verifier::Ed25519Verifier(std::string publicKeyBase64)
    : publicKeyBase64_(std::move(publicKeyBase64)),
    initResult_(validatePublicKey(publicKeyBase64_)) {}

std::expected<void, LicenseError> Ed25519Verifier::verify(
    std::string_view payload,
    std::string_view signatureBase64
    ) const {
    if (!initResult_) {
        return std::unexpected(initResult_.error());
    }

    unsigned char publicKey[crypto_sign_PUBLICKEYBYTES];
    unsigned char signature[crypto_sign_BYTES];

    if (!decodeBase64(
            publicKeyBase64_,
            publicKey,
            sizeof(publicKey),
            crypto_sign_PUBLICKEYBYTES
            )) {
        return std::unexpected(LicenseError::InvalidPublicKey);
    }

    if (!decodeBase64(
            signatureBase64,
            signature,
            sizeof(signature),
            crypto_sign_BYTES
            )) {
        return std::unexpected(LicenseError::InvalidSignature);
    }

    const auto result = crypto_sign_verify_detached(
        signature,
        reinterpret_cast<const unsigned char*>(payload.data()),
        payload.size(),
        publicKey
        );

    if (result != 0) {
        return std::unexpected(LicenseError::InvalidSignature);
    }

    return {};
}

} // namespace scanlab::license