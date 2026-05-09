import base64

from nacl.signing import SigningKey

signing_key = SigningKey.generate()
verify_key = signing_key.verify_key

private_key_base64 = base64.b64encode(
    bytes(signing_key)
).decode("ascii")

public_key_base64 = base64.b64encode(
    bytes(verify_key)
).decode("ascii")

print("PRIVATE KEY:")
print(private_key_base64)

print()

print("PUBLIC KEY:")
print(public_key_base64)