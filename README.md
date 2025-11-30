# Monefy - Personal Transaction Tracker

**Track your transactions with multi-currency support!**

## Features

- Track income and expenses
- 160+ currency conversion support
- Spending analytics by category
- Monitor scholarships, loans, and dues
- Share transaction history
- CSV data storage

## Quick Start (Windows)

### Using PowerShell (Recommended):
```powershell
# 1. Enable scripts
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

# 2. Navigate to project
cd E:\transaction-RESTapi

# 3. Run setup
.\setup_windows.ps1

# 4. Build
.\build.ps1

# 5. Run
.\monefy.exe
```

### Using Command Prompt:
```cmd
cd E:\transaction-RESTapi
setup_windows.bat
build.bat
monefy.exe
```

## Documentation

- **QUICK_START.md** - 5-minute setup guide
- **POWERSHELL_GUIDE.md** - PowerShell instructions
- **USER_GUIDE.md** - How to use features
- **TROUBLESHOOTING.md** - Fix common issues

## Main Menu Options

1. Add Transactions
2. Display total credited and debited
3. Find where you spent the most money
4. Track dues
5. Check transaction limit
6. Exit

## Currency Features

- Real-time currency conversion using REST API
- Support for 160+ currencies worldwide
- Add transactions in any currency
- Automatic conversion to base currency (default: INR)
- Live exchange rates fetched on startup

## Requirements

- Windows 10/11
- C++ Compiler (MinGW/Visual Studio)
- CURL library
- Internet (for currency features)

