# Monefy Troubleshooting Guide

Quick solutions to common problems.

---

## Build Issues

### 1. "g++ is not recognized as an internal or external command"

**Cause**: C++ compiler not installed or not in PATH

**Solutions**:

**Option A**: Install via MSYS2 (Recommended)
```cmd
# Download from https://www.msys2.org/
# Open MSYS2 terminal and run:
pacman -S mingw-w64-x86_64-gcc
```

**Option B**: Add existing compiler to PATH
1. Press `Win + X` → System → Advanced system settings
2. Environment Variables → System variables → Path → Edit
3. Add: `C:\msys64\mingw64\bin` (or your compiler location)
4. Click OK → Restart Command Prompt

**Verify**:
```cmd
g++ --version
```

---

### 2. "curl/curl.h: No such file or directory"

**Cause**: CURL library not installed

**Solution**: Install CURL via vcpkg
```cmd
# Install vcpkg if not installed
cd C:\
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat

# Install CURL
vcpkg install curl:x64-windows

# Rebuild project
cd E:\transaction-RESTapi
build.bat
```

**Alternative**: Use MSYS2
```bash
# In MSYS2 terminal
pacman -S mingw-w64-x86_64-curl
```

---

### 3. "Cannot open file 'libcurl.lib'" or linking errors

**Cause**: Linker can't find CURL library

**Solution**:

**For vcpkg installation**:
```cmd
# Update build.bat or use this command:
g++ *.o -LC:\vcpkg\installed\x64-windows\lib -lcurl -lws2_32 -o monefy.exe
```

**For MSYS2**:
```bash
g++ -std=c++17 *.cpp -lcurl -o monefy.exe
```

---

### 4. "vcpkg is not recognized"

**Cause**: vcpkg not installed or not in PATH

**Solution**: Use full path
```cmd
C:\vcpkg\vcpkg.exe install curl:x64-windows
```

Or navigate first:
```cmd
cd C:\vcpkg
vcpkg install curl:x64-windows
```

---

### 5. Build succeeds but exe is missing

**Cause**: Antivirus quarantined the executable

**Solution**:
1. Check your antivirus quarantine
2. Add project folder to antivirus exceptions
3. Rebuild: `build.bat`

---

## Runtime Issues

### 6. "Failed to fetch exchange rates"

**Causes & Solutions**:

**Cause A**: No internet connection
- Connect to internet
- App works offline but without currency features

**Cause B**: Firewall blocking
- Add `monefy.exe` to firewall exceptions
- Windows Firewall: Settings → Allow an app

**Cause C**: SSL/TLS certificate issues
```cmd
# Reinstall CURL with SSL support
cd C:\vcpkg
vcpkg remove curl:x64-windows
vcpkg install curl[ssl]:x64-windows
```

**Cause D**: API service temporarily down
- Wait a few minutes and try again
- Check https://www.exchangerate-api.com/ status

---

### 7. "Unable to open file for writing"

**Cause**: No write permissions or file locked

**Solutions**:

**Solution A**: Run as administrator
- Right-click `monefy.exe` → Run as administrator

**Solution B**: Check file permissions
- Right-click `transactions.csv` → Properties
- Uncheck "Read-only" if checked

**Solution C**: Close other programs
- Close Excel/text editors that might have CSV open
- Check Task Manager for processes using the file

---

### 8. Application crashes on startup

**Cause**: Corrupted `transactions.csv`

**Solution A**: Fix the CSV file
1. Open `transactions.csv` in Notepad
2. Check format (should be 5 fields per line):
   ```
   description,amount,type,category,currency
   ```
3. Fix or delete corrupted lines
4. Save and restart app

**Solution B**: Start fresh
```cmd
ren transactions.csv transactions.csv.backup
monefy.exe
```

**Example of valid CSV**:
```
Grocery shopping,1500.00,debit,food,INR
Monthly salary,50000.00,credit,income,INR
Movie tickets,800.00,debit,entertainment,INR
```

---

### 9. "Currency not supported"

**Cause**: Invalid currency code entered

**Solution**:
1. Use option 8 → 1 to see available currencies
2. Use standard 3-letter codes: USD, EUR, GBP, INR, etc.
3. Codes are case-insensitive (usd = USD)

**Common valid codes**:
- USD (US Dollar)
- EUR (Euro)
- GBP (British Pound)
- INR (Indian Rupee)
- JPY (Japanese Yen)
- AUD (Australian Dollar)
- CAD (Canadian Dollar)

---

### 10. Numbers/amounts not displaying correctly

**Cause**: Locale/decimal separator issues

**Solution**: Use period (.) as decimal separator
- Correct: `1500.50`
- Incorrect: `1500,50`

---

### 11. Application runs but menu is unresponsive

**Cause**: Invalid input or input buffer issues

**Solution**:
- Enter only valid menu numbers (1-10)
- Press Enter after each input
- If stuck, close and restart application

---

## Data Issues

### 12. Transactions not saving

**Cause**: File write errors

**Solutions**:

**Check**: Does `transactions.csv` exist?
```cmd
dir transactions.csv
```

**Check**: File permissions
- Right-click `transactions.csv` → Properties
- Ensure "Read-only" is unchecked

**Check**: Disk space
- Ensure drive has free space

---

### 13. Old transactions disappeared

**Cause**: CSV file replaced or corrupted

**Solution**:
1. Check for backup: `transactions.csv.backup`
2. Search for CSV files:
   ```cmd
   dir /s transactions.csv
   ```
3. Restore from backup if available
4. Check Recycle Bin

**Prevention**: Regular backups!
```cmd
copy transactions.csv transactions.csv.backup
```

---

### 14. Duplicate transactions appearing

**Cause**: Manual CSV editing errors

**Solution**:
1. Open `transactions.csv`
2. Remove duplicate lines
3. Ensure no blank lines in middle of file
4. Save and restart app

---

## Compilation Warnings

### 15. Warning: "unused variable" or similar

**Impact**: Usually harmless warnings

**Solution**: Can be ignored or fix in code if desired

---

### 16. Warning: "deprecated" features

**Impact**: Code works but may need updates in future

**Solution**: Note for future updates, doesn't affect current use

---

## Performance Issues

### 17. Application starts slowly

**Cause**: Fetching exchange rates on startup

**Solution**: Normal behavior, takes 2-5 seconds
- Requires internet connection
- If too slow, check internet speed

---

### 18. Large transaction file slows app

**Cause**: Too many transactions (>1000)

**Solution**: Archive old transactions
```cmd
# Backup current transactions
copy transactions.csv transactions_2024.csv

# Start fresh CSV with recent transactions only
# Edit transactions.csv to keep only recent entries
```

---

## Windows-Specific Issues

### 19. "Access is denied" errors

**Solution**: Run Command Prompt as Administrator
- Press `Win + X`
- Select "Command Prompt (Admin)"

---

### 20. Paths with spaces causing issues

**Solution**: Use quotes around paths
```cmd
cd "E:\My Projects\transaction-RESTapi"
```

---

### 21. MSYS2 vs MinGW vs Visual Studio confusion

**Recommendation**: Use MSYS2 for easiest setup

**MSYS2** (Recommended for beginners):
- Complete environment
- Easy package management
- Unix-like tools

**MinGW Standalone**:
- Lighter weight
- Manual configuration needed

**Visual Studio**:
- Professional IDE
- Larger download
- Full Windows integration

---

## Internet/Network Issues

### 22. Proxy preventing API access

**Solution**: Configure CURL to use proxy
```cmd
set http_proxy=http://proxy.example.com:8080
set https_proxy=http://proxy.example.com:8080
monefy.exe
```

---

### 23. Corporate firewall blocking

**Solution**: Contact IT department to allow:
- Domain: `exchangerate-api.com`
- Port: 443 (HTTPS)
- Application: `monefy.exe`

---

## Error Messages Dictionary

| Error Message | Common Cause | Quick Fix |
|---------------|--------------|-----------|
| "No such file or directory" | Missing header/file | Install dependencies |
| "Undefined reference to..." | Linking error | Check library paths |
| "Permission denied" | File permissions | Run as admin |
| "Bad allocation" | Memory issue | Restart app |
| "Invalid argument" | Wrong input format | Check input format |
| "Connection refused" | Network issue | Check internet |

---

## Getting Help

### Before Asking for Help

1. Check error message in this guide
2. Verify all prerequisites installed
3. Try rebuilding: `build.bat`
4. Check `transactions.csv` format
5. Test internet connection

### Information to Provide

When reporting issues, include:
- Windows version (Win 10/11)
- Compiler used (MinGW/MSVC)
- Full error message
- Steps to reproduce
- Contents of `transactions.csv` (if relevant)

---

## Quick Diagnostic Commands

Run these to diagnose issues:

```cmd
REM Check compiler
g++ --version

REM Check CURL
curl --version

REM Check vcpkg packages
C:\vcpkg\vcpkg.exe list

REM Check file
type transactions.csv

REM Check disk space
dir E:\

REM Test internet
ping exchangerate-api.com
```

---

## Recovery Commands

If everything breaks:

```cmd
REM 1. Backup data
copy transactions.csv transactions_backup.csv

REM 2. Clean build
del *.o *.exe

REM 3. Rebuild
build.bat

REM 4. Fresh start with backup data
ren transactions.csv transactions.csv.old
copy transactions_backup.csv transactions.csv
monefy.exe
```

---

## Still Not Working?

1. **Reinstall dependencies**:
   ```cmd
   cd C:\vcpkg
   vcpkg remove curl:x64-windows
   vcpkg install curl:x64-windows
   ```

2. **Clean reinstall**:
   - Backup `transactions.csv`
   - Delete all `.o` and `.exe` files
   - Run `build.bat`

3. **Try MSYS2 environment**:
   - Open MSYS2 MinGW 64-bit terminal
   - Navigate: `cd /e/transaction-RESTapi`
   - Build: `g++ -std=c++17 *.cpp -lcurl -o monefy.exe`
   - Run: `./monefy.exe`

---

**Most issues are resolved by ensuring dependencies are properly installed!**

See **WINDOWS_SETUP.md** for complete setup instructions.
