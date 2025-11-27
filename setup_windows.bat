@echo off
REM Monefy Windows Setup Script
REM This script automates the setup process on Windows

echo ========================================
echo Monefy - Windows Setup
echo ========================================
echo.

REM Check if running with admin privileges
net session >nul 2>&1
if %errorLevel% == 0 (
    echo Running with administrator privileges...
) else (
    echo WARNING: Not running as administrator.
    echo Some features may require admin rights.
    echo.
)

REM Check for Visual Studio or MinGW
echo Checking for C++ compiler...
where cl >nul 2>&1
if %errorLevel% == 0 (
    echo [OK] Visual Studio C++ compiler found
    set COMPILER=msvc
    goto :compiler_found
)

where g++ >nul 2>&1
if %errorLevel% == 0 (
    echo [OK] MinGW g++ compiler found
    set COMPILER=mingw
    goto :compiler_found
)

echo [ERROR] No C++ compiler found!
echo.
echo Please install one of the following:
echo   1. Visual Studio 2019+ with C++ workload
echo   2. MinGW-w64 (https://www.mingw-w64.org/)
echo   3. MSYS2 with mingw-w64-toolchain
echo.
pause
exit /b 1

:compiler_found
echo.

REM Check for CMake
echo Checking for CMake...
where cmake >nul 2>&1
if %errorLevel% == 0 (
    echo [OK] CMake found
) else (
    echo [WARNING] CMake not found!
    echo Download from: https://cmake.org/download/
    echo CMake is recommended but not required if using build.bat
    echo.
)

REM Check for vcpkg
echo Checking for vcpkg...
if exist "C:\vcpkg\vcpkg.exe" (
    echo [OK] vcpkg found at C:\vcpkg
    set VCPKG_PATH=C:\vcpkg
    goto :vcpkg_found
)

if exist "%USERPROFILE%\vcpkg\vcpkg.exe" (
    echo [OK] vcpkg found at %USERPROFILE%\vcpkg
    set VCPKG_PATH=%USERPROFILE%\vcpkg
    goto :vcpkg_found
)

echo [WARNING] vcpkg not found!
echo.
echo Do you want to install vcpkg now? (Y/N)
set /p INSTALL_VCPKG=
if /i "%INSTALL_VCPKG%"=="Y" (
    echo Installing vcpkg...
    cd %USERPROFILE%
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    call bootstrap-vcpkg.bat
    set VCPKG_PATH=%USERPROFILE%\vcpkg
    cd "%~dp0"
    goto :vcpkg_found
) else (
    echo Skipping vcpkg installation.
    echo You will need to install CURL manually.
    goto :skip_vcpkg
)

:vcpkg_found
echo.
echo Installing dependencies via vcpkg...
echo This may take several minutes...
cd /d "%VCPKG_PATH%"
vcpkg install curl:x64-windows
if %errorLevel% neq 0 (
    echo [ERROR] Failed to install dependencies
    pause
    exit /b 1
)
echo [OK] Dependencies installed
cd /d "%~dp0"

:skip_vcpkg
echo.
echo ========================================
echo Setup Complete!
echo ========================================
echo.
echo Next steps:
echo   1. Run build.bat to compile the project
echo   2. Run monefy.exe to start the application
echo   3. See USER_GUIDE.md for usage instructions
echo.
pause
