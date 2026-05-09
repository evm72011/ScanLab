param(
    [string]$Root = ".",
    [string]$Config = ".cmake-format.yaml"
)

$ErrorActionPreference = "Stop"

$cmakeFormat = $null

# 1. Try VENV_DIR
if ($env:VENV_DIR) {

    $venvExe = Join-Path $env:VENV_DIR "Scripts/cmake-format.exe"

    if (Test-Path $venvExe) {
        $cmakeFormat = $venvExe
    }
}

# 2. Fallback to PATH
if (-not $cmakeFormat) {

    $cmd = Get-Command cmake-format -ErrorAction SilentlyContinue

    if ($cmd) {
        $cmakeFormat = $cmd.Source
    }
}

if (-not $cmakeFormat) {
    Write-Error "cmake-format not found"
}

if (-not (Test-Path $Config)) {
    Write-Error "Config file not found: $Config"
}

$excludeDirs = @(
    "build",
    ".venv",
    "external",
    "_deps",
    ".git"
)

$files = Get-ChildItem $Root -Recurse -File |
    Where-Object {

        $full = $_.FullName

        foreach ($dir in $excludeDirs) {
            $escapedDir = [regex]::Escape($dir)

            if ($full -match "[\\/]$escapedDir[\\/]") {
                return $false
            }
        }

        $_.Name -eq "CMakeLists.txt" -or $_.Extension -eq ".cmake"
    }

$total = $files.Count

if ($total -eq 0) {
    Write-Host "No CMake files found."
    exit 0
}

Write-Host "Formatting $total file(s)..."

$i = 0

foreach ($file in $files) {

    $i++

    Write-Host "[$i/$total] $($file.FullName)"

    & $cmakeFormat -c $Config -i $file.FullName

    if ($LASTEXITCODE -ne 0) {
        Write-Error "cmake-format failed for $($file.FullName)"
    }
}

Write-Host "Done."