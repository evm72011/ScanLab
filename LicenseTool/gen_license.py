import base64
import json
from pathlib import Path

from nacl.signing import SigningKey


def build_payload(devices: list[str]) -> bytes:
    return "\n".join(devices).encode("utf-8")


def create_license_file(
    devices: list[str],
    private_key_base64: str,
    output_path: str | Path,
) -> None:
    devices = sorted(devices)

    payload = build_payload(devices)

    private_key_bytes = base64.b64decode(private_key_base64)
    signing_key = SigningKey(private_key_bytes)

    signature = signing_key.sign(payload).signature
    signature_base64 = base64.b64encode(signature).decode("ascii")

    license_data = {
        "devices": devices,
        "signature": signature_base64,
    }

    output_path = Path(output_path)

    with output_path.open("w", encoding="utf-8") as file:
        json.dump(license_data, file, indent=2)


if __name__ == "__main__":
    private_key_base64 = "KpKbCPOLSq4UUAbJB1nUO3IzTO9gDgV/5AUBWC8MGq0="

    devices = [
        "AA5239",
        "MOCK_12345",
        "MOCK_61890"
    ]

    create_license_file(
        devices=devices,
        private_key_base64=private_key_base64,
        output_path="license.json",
    )