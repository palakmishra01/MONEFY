# Monefy - PowerShell Guide

Complete guide for running Monefy using PowerShell on Windows.

---

## Quick Start with PowerShell

### Step 1: Open PowerShell

**Option A**: From Start Menu
1. Press `Win` key
2. Type "PowerShell"
3. Click "Windows PowerShell"

**Option B**: From File Explorer
1. Navigate to `E:\transaction-RESTapi`
2. Hold `Shift` and right-click in the folder
3. Select "Open PowerShell window here"

**Option C**: Using Run Dialog
1. Press `Win + R`
2. Type `powershell`
3. Press Enter

---

### Step 2: Enable Script Execution

PowerShell blocks scripts by default. You need to allow them:

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

**What this does**: Allows you to run locally created scripts

**If you get an error**: Right-click PowerShell and "Run as Administrator", then try again

---

### Step 3: Navigate to Project Directory

```powershell
cd E:\transaction-RESTapi
```

Or if you opened PowerShell from the folder, you're already there!

---

### Step 4: Run Setup Script

```powershell
.\setup_windows.ps1
```

**Note the `.\` prefix** - PowerShell requires this for local scripts

This will:
- Check for C++ compiler
- Install vcpkg if needed
- Install CURL library
- Set up build environment

---

### Step 5: Build the Project

```powershell
.\build.ps1
```

If successful, you'll see:
```
[SUCCESS] Build complete!
Executable: monefy.exe
```

---

### Step 6: Run the Application

```powershell
.\monefy.exe
```

---

## Common PowerShell Commands

| Task | Command |
|------|---------|
| Navigate to folder | `cd E:\transaction-RESTapi` |
| List files | `ls` or `dir` |
| Run setup | `.\setup_windows.ps1` |
| Build project | `.\build.ps1` |
| Run application | `.\monefy.exe` |
| Check compiler | `g++ --version` |
| Clear screen | `cls` or `clear` |
| Exit PowerShell | `exit` |

---

## PowerShell vs Command Prompt

### Key Differences

| Feature | PowerShell | Command Prompt |
|---------|------------|----------------|
| Script extension | `.ps1` | `.bat` |
| Run local script | `.\script.ps1` | `script.bat` |
| Variable syntax | `$variable` | `%variable%` |
| Modern features | Yes | No |
| Color output | Built-in | Limited |

### Which to Use?

**Use PowerShell** (Recommended):
- Modern, powerful features
- Better error messages
- Colored output
- Tab completion

**Use Command Prompt**:
- Simpler for basic tasks
- Legacy system compatibility

**Both work for Monefy!**

---

## Troubleshooting PowerShell Issues

### 1. "Cannot be loaded because running scripts is disabled"

**Error**:
```
.\setup_windows.ps1 : File cannot be loaded because running scripts is disabled
```

**Solution**:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

Or run as Administrator:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned
```

---

### 2. "The term 'g++' is not recognized"

**Solution**: Compiler not in PATH

```powershell
# Check if compiler exists
Get-Command g++ -ErrorAction SilentlyContinue

# If not found, add to PATH for current session:
$env:Path += ";C:\msys64\mingw64\bin"

# Verify
g++ --version
```

To add permanently:
```powershell
[Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\msys64\mingw64\bin", "User")
```

---

### 3. Script runs but nothing happens

**Cause**: Output might be hidden

**Solution**: Run with verbose output
```powershell
.\build.ps1 -Verbose
```

---

### 4. "Access to the path is denied"

**Solution**: Run PowerShell as Administrator
1. Right-click PowerShell
2. Select "Run as Administrator"
3. Navigate to project and run scripts

---

### 5. PowerShell version too old

**Check version**:
```powershell
$PSVersionTable.PSVersion
```

**Requirement**: PowerShell 5.0+ (Windows 10+ has this)

**Update if needed**:
- Download from: https://github.com/PowerShell/PowerShell/releases

---

## Advanced PowerShell Usage

### Run Specific Compiler

```powershell
# Force MinGW
$env:CC = "gcc"
$env:CXX = "g++"
.\build.ps1

# Force MSVC
$env:CC = "cl"
$env:CXX = "cl"
.\build.ps1
```

---

### Build with Custom CURL Path

```powershell
$env:CURL_INCLUDE = "C:\custom\curl\include"
$env:CURL_LIB = "C:\custom\curl\lib"
.\build.ps1
```

---

### Clean Build

```powershell
# Remove all compiled files
Remove-Item *.o, *.exe -ErrorAction SilentlyContinue

# Rebuild
.\build.ps1
```

---

### Check Dependencies

```powershell
# Check for compiler
Get-Command g++, cl -ErrorAction SilentlyContinue

# Check for CMake
Get-Command cmake -ErrorAction SilentlyContinue

# Check vcpkg packages
C:\vcpkg\vcpkg.exe list

# Test CURL
curl --version
```

---

## Useful PowerShell Aliases

Add these to your PowerShell profile for quick access:

```powershell
# Open profile
notepad $PROFILE

# Add these lines:
function Build-Monefy { .\build.ps1 }
function Run-Monefy { .\monefy.exe }
function Clean-Monefy { Remove-Item *.o, *.exe -ErrorAction SilentlyContinue }

Set-Alias build Build-Monefy
Set-Alias run Run-Monefy
Set-Alias clean Clean-Monefy
```

Then you can use:
```powershell
build  # Instead of .\build.ps1
run    # Instead of .\monefy.exe
clean  # To clean build files
```

---

## PowerShell Profile Setup

Create a permanent PowerShell profile:

```powershell
# Create profile if doesn't exist
if (!(Test-Path $PROFILE)) {
    New-Item -Path $PROFILE -ItemType File -Force
}

# Edit profile
notepad $PROFILE

# Add useful settings:
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
$env:Path += ";C:\msys64\mingw64\bin"
$env:Path += ";C:\vcpkg"

# Save and reload
. $PROFILE
```

---

## Batch vs PowerShell Scripts

Monefy includes both:

| Script | PowerShell | Batch (CMD) |
|--------|-----------|-------------|
| Setup | `setup_windows.ps1` | `setup_windows.bat` |
| Build | `build.ps1` | `build.bat` |

**Use PowerShell scripts if**:
- You prefer PowerShell
- Want colored output
- Need advanced features

**Use Batch scripts if**:
- You prefer Command Prompt
- Want simpler syntax
- Compatibility with older systems

---

## Complete PowerShell Workflow

```powershell
# 1. Open PowerShell as Admin (first time only)
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

# 2. Navigate to project
cd E:\transaction-RESTapi

# 3. Run setup (first time only)
.\setup_windows.ps1

# 4. Build project
.\build.ps1

# 5. Run application
.\monefy.exe

# 6. For rebuilds
Remove-Item *.o -ErrorAction SilentlyContinue
.\build.ps1
.\monefy.exe
```

---

## PowerShell Tips

### Tab Completion
- Type `.\b` and press `Tab` → completes to `.\build.ps1`
- Works for commands, files, and paths

### Command History
- Press `↑` (up arrow) to recall previous commands
- Press `Ctrl+R` to search command history

### Copy/Paste
- Right-click to paste in PowerShell
- Select text and press `Enter` to copy

### Clear Screen
```powershell
cls  # or clear
```

### Check if File Exists
```powershell
Test-Path monefy.exe
```

### View File Contents
```powershell
Get-Content transactions.csv
# or
cat transactions.csv
```

---

## Running Without Scripts

If you can't run `.ps1` scripts, compile manually:

```powershell
# Compile with MinGW
g++ -std=c++17 -Wall -Wextra -IC:\vcpkg\installed\x64-windows\include -c transaction.cpp
g++ -std=c++17 -Wall -Wextra -IC:\vcpkg\installed\x64-windows\include -c transaction_manager.cpp
g++ -std=c++17 -Wall -Wextra -IC:\vcpkg\installed\x64-windows\include -c currency_converter.cpp
g++ -std=c++17 -Wall -Wextra -IC:\vcpkg\installed\x64-windows\include -c main.cpp

# Link
g++ transaction.o transaction_manager.o currency_converter.o main.o -LC:\vcpkg\installed\x64-windows\lib -lcurl -lws2_32 -o monefy.exe

# Clean up
Remove-Item *.o

# Run
.\monefy.exe
```

---

## PowerShell One-Liners

```powershell
# Quick build and run
.\build.ps1; if ($?) { .\monefy.exe }

# Build with timestamp
Write-Host "Building at $(Get-Date)"; .\build.ps1

# Backup data before running
Copy-Item transactions.csv transactions.csv.backup -ErrorAction SilentlyContinue; .\monefy.exe

# Check if compiler is available
if (Get-Command g++ -ErrorAction SilentlyContinue) { "Compiler found" } else { "Install compiler!" }
```

---

## Environment Variables

Set for current session:
```powershell
$env:CURL_LIB = "C:\vcpkg\installed\x64-windows\lib"
$env:CURL_INCLUDE = "C:\vcpkg\installed\x64-windows\include"
```

Set permanently:
```powershell
[Environment]::SetEnvironmentVariable("CURL_LIB", "C:\vcpkg\installed\x64-windows\lib", "User")
```

---

## Debugging in PowerShell

```powershell
# Verbose output
$VerbosePreference = "Continue"
.\build.ps1

# Check last exit code
.\monefy.exe
Write-Host "Exit code: $LASTEXITCODE"

# Capture output
.\monefy.exe 2>&1 | Tee-Object -FilePath output.log

# Check errors only
.\build.ps1 2>&1 | Select-String "error"
```

---

## Quick Reference Card

```
SETUP COMMANDS:
  Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
  .\setup_windows.ps1

BUILD COMMANDS:
  .\build.ps1
  .\monefy.exe

HELPFUL COMMANDS:
  ls                    # List files
  cd E:\path           # Change directory
  cls                   # Clear screen
  g++ --version        # Check compiler
  Get-Help command     # Get help

SHORTCUTS:
  Tab                   # Auto-complete
  ↑/↓                  # Command history
  Ctrl+C               # Stop running program
  Ctrl+R               # Search history
```

---

## Need More Help?

- PowerShell issues → See TROUBLESHOOTING.md
- General setup → See WINDOWS_SETUP.md
- Usage help → See USER_GUIDE.md
- Quick start → See QUICK_START.md

---

**PowerShell is ready! Happy coding!**
