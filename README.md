# transaction-tracker# 🎯 CHILLAR - C++ Personal Transaction Tracker with REST API

**Your intelligent personal account manager with real-time multi-currency support!**

## ✨ Features

- 📊 **Track Transactions**: Credits, debits, categories
- 💱 **Currency Conversion**: Real-time rates via REST API
- 🌍 **Multi-Currency**: Support for 160+ currencies
- 📈 **Analytics**: Spending patterns, category analysis
- 👨‍👩‍👧‍👦 **Guardian Sharing**: Share transaction history
- 💾 **Persistent Storage**: CSV-based data management
- 🔒 **Type-Safe**: Modern C++ with exception handling

## 🚀 Quick Start

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get install build-essential libcurl4-openssl-dev nlohmann-json3-dev

# Fedora/RedHat
sudo dnf install gcc-c++ libcurl-devel nlohmann_json-devel

# macOS (Homebrew)
brew install cmake curl nlohmann-json
```

### Build & Run
```bash
# Clone/Navigate to project
cd chillar

# Option 1: Using Make (Recommended)
make run

# Option 2: Using CMake
mkdir build && cd build
cmake ..
make
./chillar

# Option 3: Manual Compilation
g++ -Wall -Wextra -std=c++17 -c *.cpp
g++ -o chillar *.o -lcurl
./chillar
```

## 📁 Project Structure

```
├── main.cpp                    # Application entry point
├── transaction.hpp/.cpp        # Transaction class
├── currency_converter.hpp/.cpp # REST API integration
├── transaction_manager.hpp/.cpp# Business logic
├── Makefile                    # Build config (Make)
├── CMakeLists.txt             # Build config (CMake)
├── install.sh                 # Auto-installer
├── SETUP_GUIDE.md             # Detailed setup
├── CONVERSION_GUIDE.md        # C→C++ changes
└── transactions.csv           # Data file (auto-created)
```

## 💡 Usage Examples

### 1. Add a Transaction
```
Menu → Option 1
Enter: Description, Amount, Type (credit/debit), Category, Currency
```

### 2. View Analytics
```
Menu → Option 2: Total credits/debits
Menu → Option 3: Most spent category
Menu → Option 4: Scholarships & loans
Menu → Option 5: Dues tracking
```

### 3. Currency Conversion (NEW!)
```
Menu → Option 8: Currency Features
  ├─ Display available currencies
  ├─ Set base currency (fetches live rates)
  ├─ Convert single transaction
  ├─ View all in different currency
  └─ Convert all to target currency
```

## 🔗 REST API Details

**API Used**: ExchangeRate-API (Free Tier)
- 160+ currencies supported
- No API key required
- Real-time exchange rates
- Updated daily

## 📚 Documentation

- **SETUP_GUIDE.md** - Complete installation & setup instructions
- **CONVERSION_GUIDE.md** - Detailed C to C++ migration guide

## 🎯 Key Features

1. **Track Transactions**: Add credits, debits with categories
2. **Analytics**: Analyze spending by category
3. **Currency Conversion**: Convert between 160+ currencies
4. **Guardian Sharing**: Share transaction history
5. **Smart Limits**: Check transaction limits
6. **Persistent Storage**: Save to CSV automatically

## 🛠️ Build Systems

### Make (Simple)
```bash
make              # Compile
make run          # Build & run
make clean        # Clean artifacts
```

### CMake (Professional)
```bash
mkdir build && cd build
cmake ..
make
```

## 👥 Team

- **B24ME1002**: Aarushi Singh
- **B24ME1040**: Krishna Mishra
- **B24EE1050**: Palak Mishra
- **B24EE1080**: Tanishka Trivedi

---

## 🎉 Ready to Get Started?

```bash
# 1. Navigate to project
cd chillar

# 2. Run installer (auto-installs dependencies)
chmod +x install.sh
./install.sh

# 3. Start using!
./chillar
```

**Enjoy tracking your transactions across currencies!** 💰🌍