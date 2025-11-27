@echo off
REM Monefy Build Script for Windows
REM Supports both MinGW and MSVC compilers

echo ========================================
echo Monefy - Build Script
echo ========================================
echo.

REM Check for compiler
where g++ >nul 2>&1
if %errorLevel% == 0 (
    set COMPILER=mingw
    goto :build_mingw
)

where cl >nul 2>&1
if %errorLevel% == 0 (
    set COMPILER=msvc
    goto :build_msvc
)

echo [ERROR] No compiler found!
echo Please install Visual Studio or MinGW-w64
pause
exit /b 1

:build_mingw
echo Using MinGW compiler...
echo.

REM Check for vcpkg CURL
if exist "C:\vcpkg\installed\x64-windows\include\curl\curl.h" (
    set CURL_INCLUDE=C:\vcpkg\installed\x64-windows\include
    set CURL_LIB=C:\vcpkg\installed\x64-windows\lib
    echo Using vcpkg CURL from C:\vcpkg
) else if exist "%USERPROFILE%\vcpkg\installed\x64-windows\include\curl\curl.h" (
    set CURL_INCLUDE=%USERPROFILE%\vcpkg\installed\x64-windows\include
    set CURL_LIB=%USERPROFILE%\vcpkg\installed\x64-windows\lib
    echo Using vcpkg CURL from %USERPROFILE%\vcpkg
) else (
    echo WARNING: vcpkg CURL not found. Trying system CURL...
    set CURL_INCLUDE=
    set CURL_LIB=
)

echo Compiling source files...
if defined CURL_INCLUDE (
    g++ -std=c++17 -Wall -Wextra -I"%CURL_INCLUDE%" -c transaction.cpp -o transaction.o
    g++ -std=c++17 -Wall -Wextra -I"%CURL_INCLUDE%" -c transaction_manager.cpp -o transaction_manager.o
    g++ -std=c++17 -Wall -Wextra -I"%CURL_INCLUDE%" -c currency_converter.cpp -o currency_converter.o
    g++ -std=c++17 -Wall -Wextra -I"%CURL_INCLUDE%" -c main.cpp -o main.o
) else (
    g++ -std=c++17 -Wall -Wextra -c transaction.cpp -o transaction.o
    g++ -std=c++17 -Wall -Wextra -c transaction_manager.cpp -o transaction_manager.o
    g++ -std=c++17 -Wall -Wextra -c currency_converter.cpp -o currency_converter.o
    g++ -std=c++17 -Wall -Wextra -c main.cpp -o main.o
)

if %errorLevel% neq 0 (
    echo [ERROR] Compilation failed!
    pause
    exit /b 1
)

echo Linking...
if defined CURL_LIB (
    g++ transaction.o transaction_manager.o currency_converter.o main.o -L"%CURL_LIB%" -lcurl -lws2_32 -o monefy.exe
) else (
    g++ transaction.o transaction_manager.o currency_converter.o main.o -lcurl -lws2_32 -o monefy.exe
)

if %errorLevel% neq 0 (
    echo [ERROR] Linking failed!
    echo.
    echo Make sure CURL library is installed:
    echo   - Via vcpkg: vcpkg install curl:x64-windows
    echo   - Or download from: https://curl.se/windows/
    pause
    exit /b 1
)

echo Cleaning up...
del *.o

echo.
echo [SUCCESS] Build complete!
echo Executable: monefy.exe
echo.
echo Run 'monefy.exe' to start the application
pause
goto :end

:build_msvc
echo Using Visual Studio compiler...
echo.
echo Building with CMake...

if not exist build mkdir build
cd build

REM Try with vcpkg toolchain
if exist "C:\vcpkg\scripts\buildsystems\vcpkg.cmake" (
    cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
) else if exist "%USERPROFILE%\vcpkg\scripts\buildsystems\vcpkg.cmake" (
    cmake .. -DCMAKE_TOOLCHAIN_FILE=%USERPROFILE%\vcpkg\scripts\buildsystems\vcpkg.cmake
) else (
    echo WARNING: vcpkg toolchain not found, building without it...
    cmake ..
)

if %errorLevel% neq 0 (
    echo [ERROR] CMake configuration failed!
    cd ..
    pause
    exit /b 1
)

cmake --build . --config Release

if %errorLevel% neq 0 (
    echo [ERROR] Build failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo [SUCCESS] Build complete!
echo Executable: build\Release\monefy.exe
echo.

cd ..
if exist "build\Release\monefy.exe" (
    copy "build\Release\monefy.exe" "monefy.exe" >nul
    echo Copied executable to root directory
)

pause

:end
