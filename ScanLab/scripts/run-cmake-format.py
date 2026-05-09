#!/usr/bin/env python

import argparse
import os
import subprocess
import sys
from pathlib import Path


EXCLUDED_DIRS = {
    "build",
    ".venv",
    "external",
    "_deps",
    ".git",
}


def find_cmake_format(root: Path) -> Path | str:
    venv_dir = os.environ.get("VENV_DIR")

    if venv_dir:
        venv = Path(venv_dir)

        candidates = [
            venv / "Scripts" / "cmake-format.exe",
            venv / "bin" / "cmake-format",
        ]

        for candidate in candidates:
            if candidate.exists():
                return candidate

    return "cmake-format"


def should_skip(path: Path) -> bool:
    return any(part in EXCLUDED_DIRS for part in path.parts)


def collect_files(root: Path) -> list[Path]:
    result: list[Path] = []

    for path in root.rglob("*"):
        if not path.is_file():
            continue

        rel = path.relative_to(root)

        if should_skip(rel):
            continue

        if path.name == "CMakeLists.txt" or path.suffix == ".cmake":
            result.append(path)

    return sorted(result)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("root", nargs="?", default=".")
    parser.add_argument("config", nargs="?", default=".cmake-format.yaml")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    root = Path(args.root).resolve()
    config = Path(args.config).resolve()

    if not config.exists():
        print(f"Config file not found: {config}", file=sys.stderr)
        return 1

    cmake_format = find_cmake_format(root)

    files = collect_files(root)

    if not files:
        print("No CMake files found.")
        return 0

    print(f"Formatting {len(files)} file(s) using config: {config}")

    for index, file in enumerate(files, start=1):
        print(f"[{index}/{len(files)}] {file}")

        cmd = [
            str(cmake_format),
            "-c",
            str(config),
        ]

        if args.check:
            cmd.append(str(file))
        else:
            cmd.extend(["-i", str(file)])

        result = subprocess.run(cmd)

        if result.returncode != 0:
            return result.returncode

    print("Done.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())