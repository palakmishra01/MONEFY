# CHILLAR - C++ Personal Transaction Tracker with Currency Conversion

Your personal account manager with REST API integration for real-time currency conversion.

## 🎯 Project Overview

CHILLAR is now built in **C++** with the following features:
- ✅ Track income (credits) and expenses (debits)
- ✅ Categorize transactions
- ✅ Real-time currency conversion via REST API
- ✅ View transactions in multiple currencies
- ✅ Track scholarships, loans, and dues
- ✅ Multi-currency support (INR, USD, EUR, GBP, JPY, etc.)
- ✅ Guardian sharing features
- ✅ Transaction limit checking

## 📋 Project Structure

```
├── main.cpp                      # Main application with menu system
├── transaction.hpp/.cpp          # Transaction class definition and methods
├── currency_converter.hpp/.cpp   # REST API integration for currency conversion
├── transaction_manager.hpp/.cpp  # Transaction management and analytics
├── Makefile                      # Build configuration
├── transactions.csv              # Data storage (auto-generated)
└── README.md                     # This file
```

## 🔧 Prerequisites & Dependencies

### Required System Packages:
- **g++ 7.0+** or clang++
- **libcurl-dev** - For HTTP requests
- **Build essentials**

### C++ Libraries:
- **nlohmann/json** - Header-only JSON library (included in most distributions)
- **libcurl** - HTTP client library

### Installation on Different Systems:

#### Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install build-essential curl libcurl4-openssl-dev nlohmann-json3-dev
```

#### Fedora/RedHat:
```bash
sudo dnf install gcc-c++ libcurl-devel nlohmann_json-devel
```

#### macOS (using Homebrew):
```bash
brew install cmake curl nlohmann-json
```

#### Windows (using MinGW or Visual Studio):
- Download and install MinGW-w64 or Visual Studio Build Tools
- Install vcpkg for package management
- Install curl and nlohmann/json through vcpkg

## 🚀 Installation & Compilation

### Quick Start:
```bash
# Navigate to project directory
cd chillar

# Compile
make

# Run
make run
```

### Manual Compilation (if make not available):
```bash
g++ -Wall -Wextra -std=c++17 -c main.cpp
g++ -Wall -Wextra -std=c++17 -c transaction.cpp
g++ -Wall -Wextra -std=c++17 -c currency_converter.cpp
g++ -Wall -Wextra -std=c++17 -c transaction_manager.cpp

g++ -o chillar main.o transaction.o currency_converter.o transaction_manager.o -lcurl
./chillar
```

### Build Commands:
```bash
make              # Compile the project
make run          # Compile and run
make clean        # Remove build artifacts
make rebuild      # Clean and recompile
```

## 📖 Usage Guide

### Main Menu Options:

1. **Add Transactions**
   - Enter description, amount, type (credit/debit), category, and currency
   - Transactions are automatically saved to CSV

2. **Display Credit/Debit Summary**
   - Shows total credits, debits, and net balance
   - All in your default currency

3. **Find Most Spent Category**
   - Analyzes all debit transactions
   - Displays category with highest spending

4. **Track Scholarships and Loans**
   - Displays total scholarships received
   - Displays total loans taken

5. **Track Dues**
   - Shows money lent to others (tracked in 'dues' category)

6. **Share with Guardian**
   - Displays all transactions in readable format
   - Can be shared with parents/guardians

7. **Check Transaction Limit**
   - Enter a limit amount
   - Displays all transactions exceeding the limit

8. **Currency Conversion Features** ⭐ NEW
   - Display available currencies
   - Set base currency for exchange rates
   - Convert specific transactions
   - View all transactions in different currencies
   - Convert all transactions to a target currency

9. **Display All Transactions**
   - Shows all transactions with details

10. **Exit**
    - Saves all data and exits the program

## 💱 Currency Conversion Features

### How REST API Integration Works:

The application uses **ExchangeRate-API** (free tier) to fetch real-time exchange rates:
- Base URL: `https://api.exchangerate-api.com/v4/latest/`
- Returns rates for 160+ currencies
- No API key required for free tier

### Supported Operations:

```
Set Base Currency → Fetch Exchange Rates → Convert Transactions → View Results
```

### Currency Code Examples:
- **INR** - Indian Rupee
- **USD** - US Dollar
- **EUR** - Euro
- **GBP** - British Pound
- **JPY** - Japanese Yen
- **AUD** - Australian Dollar
- **CAD** - Canadian Dollar
- **CHF** - Swiss Franc

### Example Workflow:
1. Add transaction in USD
2. Go to Currency Conversion Features
3. Set base currency to INR (fetches INR-to-all-currencies rates)
4. View all transactions in INR
5. Or convert specific transaction to EUR

## 📊 Data Storage Format

Transactions are stored in `transactions.csv`:
```csv
description,amount,type,category,currency
Lunch with friends,250.50,debit,food,INR
Scholarship received,5000.00,credit,education,INR
International transfer,100.00,debit,transfer,USD
```

## 🔍 Technical Details

### Class Architecture:

**Transaction Class:**
- Encapsulates individual transaction data
- Methods for getters, setters, display, and CSV serialization

**CurrencyConverter Class:**
- Handles all REST API calls via libcurl
- Parses JSON responses using nlohmann/json
- Manages exchange rate caching
- Provides conversion methods

**TransactionManager Class:**
- Manages collection of transactions
- Implements file I/O (load/save)
- Provides analytics and conversion features
- Handles user interactions

**ChillarApp Class:**
- Main application controller
- Menu system and navigation
- Coordinates between managers and converters

### REST API Integration:

```cpp
// Fetch exchange rates
CurrencyConverter converter("");
converter.fetchExchangeRates("INR");

// Convert amount
float converted = converter.convertCurrency(100, "INR", "USD");
```

## 🛡️ Error Handling

The application handles:
- Network failures gracefully
- Invalid currency codes
- Missing files (creates new)
- JSON parsing errors
- File I/O errors
- Limit exceeded on transactions

## 🎨 Color-Coded Output

- 🔴 **Red** - Errors and warnings
- 🟢 **Green** - Success messages and input prompts
- 🔵 **Cyan** - Output and results
- 🟡 **Yellow** - Menu and headers
- 🟣 **Magenta** - Welcome and exit messages

## 💡 Tips & Best Practices

1. **Always set base currency first** before viewing transactions in different currencies
2. **Use consistent currency codes** (always uppercase)
3. **Check transaction limits regularly** to manage spending
4. **Backup your transactions.csv file** periodically
5. **Use meaningful category names** for better analytics

## 🐛 Troubleshooting

### Compilation Errors:

**"nlohmann/json.hpp: No such file"**
```bash
# Ubuntu/Debian
sudo apt-get install nlohmann-json3-dev

# Or download manually
wget https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp
mv json.hpp /usr/local/include/nlohmann/
```

**"curl/curl.h: No such file"**
```bash
# Ubuntu/Debian
sudo apt-get install libcurl4-openssl-dev

# Fedora
sudo dnf install libcurl-devel
```

### Runtime Errors:

**"Failed to fetch exchange rates"**
- Check internet connection
- Verify ExchangeRate-API is accessible
- Try setting a different base currency

**"transactions.csv not found"**
- Normal on first run, file will be created
- Ensure write permissions in directory

## 📈 Future Enhancements

Potential features for future versions:
- Database backend (SQLite/PostgreSQL)
- Graphical UI (Qt/wxWidgets)
- Mobile companion app
- Budget forecasting
- Expense reports
- Multi-user support
- Cloud sync
- Historical exchange rate tracking

## 🤝 Contributors

- B24EE1050: Palak Mishra

## 📝 License

This project is open source and available for educational purposes.

## 🙏 Acknowledgments

- **ExchangeRate-API** - Free exchange rate data
- **nlohmann/json** - JSON parsing library
- **libcurl** - HTTP client library
- **C++ Standard Library** - Core functionality

---

**Questions?** Check the API documentation or review the source code comments.

**Happy tracking!** 💰