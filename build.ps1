# Monefy Build Script for Windows (PowerShell)
# Supports both MinGW and MSVC compilers

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Monefy - Build Script (PowerShell)" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

$compiler = $null

# Check for compiler
if (Get-Command g++ -ErrorAction SilentlyContinue) {
    $compiler = "mingw"
    Write-Host "Using MinGW compiler..." -ForegroundColor Green
    Write-Host ""

    # Check for vcpkg CURL
    $curlInclude = $null
    $curlLib = $null

    if (Test-Path "C:\vcpkg\installed\x64-windows\include\curl\curl.h") {
        $curlInclude = "C:\vcpkg\installed\x64-windows\include"
        $curlLib = "C:\vcpkg\installed\x64-windows\lib"
        Write-Host "Using vcpkg CURL from C:\vcpkg" -ForegroundColor Green
    }
    elseif (Test-Path "$env:USERPROFILE\vcpkg\installed\x64-windows\include\curl\curl.h") {
        $curlInclude = "$env:USERPROFILE\vcpkg\installed\x64-windows\include"
        $curlLib = "$env:USERPROFILE\vcpkg\installed\x64-windows\lib"
        Write-Host "Using vcpkg CURL from $env:USERPROFILE\vcpkg" -ForegroundColor Green
    }
    else {
        Write-Host "WARNING: vcpkg CURL not found. Trying system CURL..." -ForegroundColor Yellow
    }

    Write-Host "Compiling source files..." -ForegroundColor Cyan

    # Compile source files
    $sourceFiles = @("transaction.cpp", "transaction_manager.cpp", "currency_converter.cpp", "main.cpp")

    foreach ($file in $sourceFiles) {
        if ($curlInclude) {
            & g++ -std=c++17 -Wall -Wextra -I"$curlInclude" -c $file
        }
        else {
            & g++ -std=c++17 -Wall -Wextra -c $file
        }

        if ($LASTEXITCODE -ne 0) {
            Write-Host "[ERROR] Compilation of $file failed!" -ForegroundColor Red
            Pause
            exit 1
        }
    }

    Write-Host "Linking..." -ForegroundColor Cyan

    # Link
    if ($curlLib) {
        & g++ transaction.o transaction_manager.o currency_converter.o main.o -L"$curlLib" -lcurl -lws2_32 -o monefy.exe
    }
    else {
        & g++ transaction.o transaction_manager.o currency_converter.o main.o -lcurl -lws2_32 -o monefy.exe
    }

    if ($LASTEXITCODE -ne 0) {
        Write-Host "[ERROR] Linking failed!" -ForegroundColor Red
        Write-Host ""
        Write-Host "Make sure CURL library is installed:" -ForegroundColor Yellow
        Write-Host "  - Via vcpkg: vcpkg install curl:x64-windows"
        Write-Host "  - Or download from: https://curl.se/windows/"
        Pause
        exit 1
    }

    Write-Host "Cleaning up..." -ForegroundColor Cyan
    Remove-Item *.o -ErrorAction SilentlyContinue

    Write-Host ""
    Write-Host "[SUCCESS] Build complete!" -ForegroundColor Green
    Write-Host "Executable: monefy.exe" -ForegroundColor Green
    Write-Host ""
    Write-Host "Run '.\monefy.exe' to start the application" -ForegroundColor Yellow
}
elseif (Get-Command cl -ErrorAction SilentlyContinue) {
    $compiler = "msvc"
    Write-Host "Using Visual Studio compiler..." -ForegroundColor Green
    Write-Host ""
    Write-Host "Building with CMake..." -ForegroundColor Cyan

    # Create build directory
    if (-not (Test-Path "build")) {
        New-Item -ItemType Directory -Path "build" | Out-Null
    }

    Push-Location build

    # Try with vcpkg toolchain
    if (Test-Path "C:\vcpkg\scripts\buildsystems\vcpkg.cmake") {
        & cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
    }
    elseif (Test-Path "$env:USERPROFILE\vcpkg\scripts\buildsystems\vcpkg.cmake") {
        & cmake .. -DCMAKE_TOOLCHAIN_FILE=$env:USERPROFILE/vcpkg/scripts/buildsystems/vcpkg.cmake
    }
    else {
        Write-Host "WARNING: vcpkg toolchain not found, building without it..." -ForegroundColor Yellow
        & cmake ..
    }

    if ($LASTEXITCODE -ne 0) {
        Write-Host "[ERROR] CMake configuration failed!" -ForegroundColor Red
        Pop-Location
        Pause
        exit 1
    }

    & cmake --build . --config Release

    if ($LASTEXITCODE -ne 0) {
        Write-Host "[ERROR] Build failed!" -ForegroundColor Red
        Pop-Location
        Pause
        exit 1
    }

    Write-Host ""
    Write-Host "[SUCCESS] Build complete!" -ForegroundColor Green
    Write-Host "Executable: build\Release\monefy.exe" -ForegroundColor Green
    Write-Host ""

    Pop-Location

    if (Test-Path "build\Release\monefy.exe") {
        Copy-Item "build\Release\monefy.exe" "monefy.exe" -Force
        Write-Host "Copied executable to root directory" -ForegroundColor Green
    }
}
else {
    Write-Host "[ERROR] No compiler found!" -ForegroundColor Red
    Write-Host "Please install Visual Studio or MinGW-w64" -ForegroundColor Yellow
    Pause
    exit 1
}

Write-Host ""
Pause
