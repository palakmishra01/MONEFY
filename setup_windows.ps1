# Monefy Windows Setup Script (PowerShell)
# This script automates the setup process on Windows using PowerShell

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Monefy - Windows Setup (PowerShell)" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Check for Administrator privileges
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if ($isAdmin) {
    Write-Host "[OK] Running with administrator privileges..." -ForegroundColor Green
} else {
    Write-Host "[WARNING] Not running as administrator." -ForegroundColor Yellow
    Write-Host "Some features may require admin rights." -ForegroundColor Yellow
    Write-Host ""
}

# Check for C++ compiler
Write-Host "Checking for C++ compiler..." -ForegroundColor Cyan
$compiler = $null

if (Get-Command cl -ErrorAction SilentlyContinue) {
    Write-Host "[OK] Visual Studio C++ compiler found" -ForegroundColor Green
    $compiler = "msvc"
}
elseif (Get-Command g++ -ErrorAction SilentlyContinue) {
    Write-Host "[OK] MinGW g++ compiler found" -ForegroundColor Green
    $compiler = "mingw"
}
else {
    Write-Host "[ERROR] No C++ compiler found!" -ForegroundColor Red
    Write-Host ""
    Write-Host "Please install one of the following:" -ForegroundColor Yellow
    Write-Host "  1. Visual Studio 2019+ with C++ workload"
    Write-Host "  2. MinGW-w64 (https://www.mingw-w64.org/)"
    Write-Host "  3. MSYS2 with mingw-w64-toolchain (Recommended)"
    Write-Host ""
    Write-Host "For MSYS2 (Easiest):"
    Write-Host "  1. Download from https://www.msys2.org/"
    Write-Host "  2. Install and run MSYS2"
    Write-Host "  3. Run: pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-curl"
    Write-Host "  4. Add C:\msys64\mingw64\bin to your PATH"
    Write-Host ""
    Pause
    exit 1
}

Write-Host ""

# Check for CMake
Write-Host "Checking for CMake..." -ForegroundColor Cyan
if (Get-Command cmake -ErrorAction SilentlyContinue) {
    Write-Host "[OK] CMake found" -ForegroundColor Green
} else {
    Write-Host "[WARNING] CMake not found!" -ForegroundColor Yellow
    Write-Host "Download from: https://cmake.org/download/" -ForegroundColor Yellow
    Write-Host "CMake is recommended but not required if using build.ps1" -ForegroundColor Yellow
    Write-Host ""
}

# Check for vcpkg
Write-Host "Checking for vcpkg..." -ForegroundColor Cyan
$vcpkgPath = $null

if (Test-Path "C:\vcpkg\vcpkg.exe") {
    Write-Host "[OK] vcpkg found at C:\vcpkg" -ForegroundColor Green
    $vcpkgPath = "C:\vcpkg"
}
elseif (Test-Path "$env:USERPROFILE\vcpkg\vcpkg.exe") {
    Write-Host "[OK] vcpkg found at $env:USERPROFILE\vcpkg" -ForegroundColor Green
    $vcpkgPath = "$env:USERPROFILE\vcpkg"
}
else {
    Write-Host "[WARNING] vcpkg not found!" -ForegroundColor Yellow
    Write-Host ""
    $installVcpkg = Read-Host "Do you want to install vcpkg now? (Y/N)"

    if ($installVcpkg -eq "Y" -or $installVcpkg -eq "y") {
        Write-Host "Installing vcpkg..." -ForegroundColor Cyan

        Set-Location $env:USERPROFILE
        git clone https://github.com/microsoft/vcpkg.git

        if ($LASTEXITCODE -ne 0) {
            Write-Host "[ERROR] Failed to clone vcpkg. Make sure git is installed." -ForegroundColor Red
            Pause
            exit 1
        }

        Set-Location vcpkg
        .\bootstrap-vcpkg.bat

        if ($LASTEXITCODE -ne 0) {
            Write-Host "[ERROR] Failed to bootstrap vcpkg." -ForegroundColor Red
            Pause
            exit 1
        }

        $vcpkgPath = "$env:USERPROFILE\vcpkg"
        Set-Location $PSScriptRoot
    }
    else {
        Write-Host "Skipping vcpkg installation." -ForegroundColor Yellow
        Write-Host "You will need to install CURL manually." -ForegroundColor Yellow
        Write-Host ""
        Pause
        exit 0
    }
}

# Install dependencies via vcpkg
if ($vcpkgPath) {
    Write-Host ""
    Write-Host "Installing dependencies via vcpkg..." -ForegroundColor Cyan
    Write-Host "This may take several minutes..." -ForegroundColor Yellow

    Push-Location $vcpkgPath
    .\vcpkg.exe install curl:x64-windows

    if ($LASTEXITCODE -ne 0) {
        Write-Host "[ERROR] Failed to install dependencies" -ForegroundColor Red
        Pop-Location
        Pause
        exit 1
    }

    Write-Host "[OK] Dependencies installed" -ForegroundColor Green
    Pop-Location
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Setup Complete!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Yellow
Write-Host "  1. Run .\build.ps1 to compile the project"
Write-Host "  2. Run .\monefy.exe to start the application"
Write-Host "  3. See USER_GUIDE.md for usage instructions"
Write-Host ""
Pause
