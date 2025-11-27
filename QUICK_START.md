# Monefy - Quick Start Guide

**Get up and running in 5 minutes!**

---

## Step-by-Step Instructions (Windows)

### Step 1: Install Required Software

#### Install a C++ Compiler

**Easiest Option - MinGW via MSYS2:**

1. Download MSYS2: https://www.msys2.org/
2. Run the installer (keep default location: `C:\msys64`)
3. Open "MSYS2 MSYS" from Start Menu
4. Run these commands:
   ```bash
   pacman -Syu
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-curl git
   ```
5. Add to Windows PATH:
   - Press `Win + X` → System → Advanced → Environment Variables
   - Under "System variables", select "Path" → Edit → New
   - Add: `C:\msys64\mingw64\bin`
   - Click OK on all windows

6. **Verify**: Open new Command Prompt and type:
   ```cmd
   g++ --version
   ```
   You should see version information.

---

### Step 2: Get to Your Project Directory

1. Open Command Prompt (press `Win + R`, type `cmd`, press Enter)
2. Navigate to project:
   ```cmd
   cd E:\transaction-RESTapi
   ```

---

### Step 3: Build the Project

Simply run:
```cmd
build.bat
```

If you see `[SUCCESS] Build complete!`, you're ready!

**If build fails**, you may need vcpkg:

```cmd
cd C:\
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg install curl:x64-windows
cd E:\transaction-RESTapi
build.bat
```

---

### Step 4: Run the Application

```cmd
monefy.exe
```

You should see:
```
========================================
    WELCOME TO Monefy!
  Your personal account manager
   Now with Currency Conversion!
========================================
Initializing exchange rates for INR...
Ready to use!
```

---

## First Steps with Monefy

### Add Your First Transaction

1. Press `1` (Add Transaction)
2. Fill in the details:
   ```
   Enter description: Test Purchase
   Enter amount: 100
   Enter type (credit/debit): debit
   Enter category: shopping
   Enter currency code (default INR): [press Enter for default]
   ```

3. Success! Transaction added.

### View Your Transactions

1. Press `9` (Display all transactions)
2. You'll see your transaction listed

### Try Currency Conversion

1. Press `8` (Currency Conversion)
2. Press `1` (Display available currencies)
3. See 160+ currencies and exchange rates!

---

## Common Issues

### Issue: "g++ is not recognized"

**Solution**:
- Make sure you added `C:\msys64\mingw64\bin` to PATH
- Restart Command Prompt after adding to PATH

### Issue: "Failed to fetch exchange rates"

**Solution**:
- Check your internet connection
- The app works offline but without currency features

### Issue: Build fails with CURL errors

**Solution**: Install CURL via vcpkg (see Step 3 alternative instructions)

---

## What's Next?

- **Read USER_GUIDE.md** for complete feature documentation
- **Read WINDOWS_SETUP.md** for detailed Windows setup
- **Explore the app** and try all features!

---

## Essential Commands

| What | Command |
|------|---------|
| Build | `build.bat` |
| Run | `monefy.exe` |
| Rebuild | `del monefy.exe` then `build.bat` |

---

## File Structure

```
E:\transaction-RESTapi\
├── monefy.exe           ← Your application (run this!)
├── transactions.csv      ← Your data (auto-created)
├── build.bat            ← Build script
├── USER_GUIDE.md        ← How to use features
├── WINDOWS_SETUP.md     ← Detailed setup guide
└── QUICK_START.md       ← This file
```

---

## Still Having Issues?

1. **Check you have internet** (needed for currency features)
2. **See WINDOWS_SETUP.md** for detailed troubleshooting
3. **Try MSYS2 terminal** instead of Windows cmd

---

**You're all set! Start tracking your transactions!**
