$ErrorActionPreference = "Stop"

$Root = Resolve-Path "$PSScriptRoot\.."
$Conan = Join-Path $Root ".venv\Scripts\conan.exe"
$BuildDir = Join-Path $Root "build\Desktop_Qt_6_11_0_MSVC2022_64bit-Debug"

if (!(Test-Path $Conan)) { throw "Conan not found in venv: $Conan" }

New-Item -ItemType Directory -Force -Path $BuildDir | Out-Null

& $Conan install "$Root" `
  -of "$BuildDir" `
  -s:h build_type=Debug `
  -s:h compiler.cppstd=23 `
  -c tools.microsoft.msbuild:vs_version=18 `
  -b missing
