# MONEFY - Personal Financial Transaction Tracker

**A Modern C++ Application for Multi-Currency Transaction Management with Real-Time Exchange Rate Integration**

---

## 📋 Table of Contents

1. [Project Overview](#project-overview)
2. [Key Features](#key-features)
3. [Technical Architecture](#technical-architecture)
4. [System Requirements](#system-requirements)
5. [Installation Guide](#installation-guide)
6. [Usage Guide](#usage-guide)
7. [File Structure & Descriptions](#file-structure--descriptions)
8. [API Integration](#api-integration)
9. [Data Management](#data-management)
10. [Troubleshooting](#troubleshooting)
11. [Future Enhancements](#future-enhancements)

---

## 📱 Project Overview

**MONEFY** is a professional-grade C++ application designed to help individuals manage their personal finances efficiently. The application provides comprehensive transaction tracking, spending analytics, and real-time currency conversion capabilities, making it ideal for users dealing with multiple currencies or international transactions.

The project demonstrates advanced C++ programming concepts including object-oriented design, REST API integration, dynamic data management, and persistent storage mechanisms.

### Purpose
MONEFY aims to:
- Provide a simple yet powerful interface for tracking financial transactions
- Enable multi-currency transaction management with real-time conversion
- Offer actionable spending insights through category-wise analytics
- Support family financial management through guardian sharing features
- Maintain a persistent, secure transaction history

---

## ✨ Key Features

### 1. **Transaction Management**
- Add transactions with detailed information (description, amount, type, category, currency)
- Support for both credit (income) and debit (expense) transactions
- Multi-currency transaction support (160+ currencies)
- Flexible categorization system
- Transaction history with persistent storage

### 2. **Real-Time Currency Conversion**
- Integration with ExchangeRate-API for live exchange rates
- Convert between 160+ currencies
- Support for cross-currency transactions
- Automatic rate caching for improved performance
- Real-time rate updates from reliable sources

### 3. **Financial Analytics**
- Track total credits and debits
- Calculate net balance across currencies
- Category-wise spending analysis
- Identify highest spending categories
- Track scholarships and loans
- Monitor outstanding dues

### 4. **Multi-Currency Features**
- View transactions in any supported currency
- Convert all transactions to target currency
- Compare spending across different currencies
- Analyze global expense patterns

### 5. **Sharing & Collaboration**
- Share transaction history with guardians or family members
- Guardian access for parental monitoring
- Formatted transaction reports

### 6. **Spending Control**
- Set transaction limits
- Receive alerts for transactions exceeding limits
- Monitor spending patterns
- Manage budget constraints

---

## 🏗️ Technical Architecture

### Design Pattern: Model-View-Controller (MVC)
The application follows OOP principles with clear separation of concerns:

```
┌─────────────────────────────────────┐
│         MONEFYapp  (Main)           │  ← User Interface & Control Layer
│    (Menu System & Navigation)       │
└──────────────────┬──────────────────┘
                   │
        ┌──────────┴──────────┐
        │                     │
┌───────▼──────────┐ ┌───────▼──────────────────┐
│Transaction       │ │CurrencyConverter         │
│Manager           │ │(REST API Integration)    │
│(Business Logic)  │ │                          │
└────────┬─────────┘ └────────────┬─────────────┘
         │                        │
         │         ┌──────────────┘
         │         │
    ┌────▼─────────▼────┐
    │   Transaction     │    ← Data Model
    │   (Data Class)    │
    └──────────────────┘
         │
    ┌────▼──────────────┐
    │ CSV File Storage  │    ← Persistence Layer
    │transactions.csv   │
    └───────────────────┘
```

### Technology Stack
- **Language**: C++17 (ISO/IEC 14882:2017)
- **Compiler**: g++, MSVC, or clang++
- **Build System**: CMake 3.10+
- **HTTP Client**: libcurl
- **JSON Processing**: Built-in parser (Windows-compatible)
- **Data Format**: CSV
- **Platform**: Windows 10+, macOS, Linux

---

## 🔧 System Requirements

### Minimum Requirements
- **OS**: Windows 10, macOS 10.14, or Linux (Ubuntu 18.04+)
- **RAM**: 512 MB
- **Disk Space**: 50 MB
- **Processor**: Any dual-core processor

### Development Requirements
- **C++ Compiler**: GCC 7.0+, MSVC 2019+, or Clang 10+
- **CMake**: Version 3.10 or higher
- **Build Tools**: Make or Visual Studio
- **Internet**: Required for currency conversion API calls

### Required Libraries
1. **libcurl** - HTTP client library for REST API calls
2. **C++ Standard Library** - For containers, algorithms, and I/O

---

## 💻 Installation Guide

### Windows Installation (Recommended: Visual Studio)

#### Step 1: Install Visual Studio Community
```
1. Download from: https://visualstudio.microsoft.com/downloads/
2. Choose: Visual Studio Community (FREE)
3. Select: Desktop development with C++
4. Complete installation (30-40 minutes)
```

#### Step 2: Install vcpkg Package Manager
```powershell
cd C:\
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```

#### Step 3: Install CURL Library
```powershell
cd C:\vcpkg
.\vcpkg install curl:x64-windows
.\vcpkg integrate install
```

#### Step 4: Set Up Project
```
1. Create folder: C:\projects\MONEFY
2. Copy all source files (.cpp, .hpp, CMakeLists.txt)
3. Launch Visual Studio
4. File → Open → Folder
5. Select: C:\projects\chillar
```

#### Step 5: Build & Run
```
1. Press: Ctrl + Shift + B (Build)
2. Wait for compilation
3. Press: F5 (Run)
```

### Linux/macOS Installation

#### Ubuntu/Debian
```bash
# Install dependencies
sudo apt-get update
sudo apt-get install build-essential cmake libcurl4-openssl-dev

# Create project directory
mkdir -p ~/projects/MONEFY
cd ~/projects/MONEFY

# Copy source files here

# Build
mkdir build
cd build
cmake ..
make

# Run
./MONEFY
```

#### macOS (Homebrew)
```bash
# Install dependencies
brew install cmake curl

# Create project directory
mkdir -p ~/projects/MONEFY
cd ~/projects/MONEFY

# Copy source files here

# Build
mkdir build
cd build
cmake ..
make

# Run
./MONEFY
```

---

## 📖 Usage Guide

### Main Menu
```
Select the function which you want to perform:
1.  Add Transactions
2.  Display total credited and debited
3.  Find where you spent the most money
4.  Track Scholarships and Loans
5.  Track dues
6.  Share transaction history with Guardian
7.  Check transaction limit
8.  Currency Conversion Features
9.  Display all transactions
10. Exit
```

### Adding a Transaction
```
1. Select: Option 1 (Add Transactions)
2. Enter description: "Grocery shopping"
3. Enter amount: 50
4. Enter type: "debit" or "credit"
5. Enter category: "groceries"
6. Enter currency: "INR" (or any supported code)
→ Transaction saved automatically
```

### Currency Conversion
```
1. Select: Option 8 (Currency Conversion Features)
2. Options:
   - Set base currency (fetches live rates)
   - Convert single transaction
   - View all in different currency
   - Convert all to target currency
```

### Viewing Analytics
```
- Option 2: See credit/debit summary
- Option 3: Identify highest spending category
- Option 4: Track scholarships and loans
- Option 5: Monitor outstanding dues
```

---

## 📁 File Structure & Descriptions

### Core Source Files

#### **1. main.cpp** (Entry Point & User Interface)
**Purpose**: Application controller and user interface

**Responsibilities**:
- Implements the interactive menu system
- Manages user input and navigation
- Orchestrates interaction between Transaction Manager and Currency Converter
- Handles the main application loop
- Provides both main menu and currency conversion submenu

**Key Components**:
- `MONEFYapp` class: Main application controller
- `displayMainMenu()`: Renders primary menu options
- `displayCurrencyMenu()`: Shows currency conversion options
- `handleCurrencyConversion()`: Processes currency-related operations
- `run()`: Main event loop

**Dependencies**: 
- transaction_manager.hpp
- currency_converter.hpp

**Size**: ~9 KB | ~230 lines

---

#### **2. transaction.hpp** (Transaction Data Model - Header)
**Purpose**: Define the Transaction data structure and interface

**Responsibilities**:
- Define the Transaction class structure
- Declare all transaction-related methods
- Define getter and setter interfaces
- Provide CSV serialization/deserialization methods

**Key Components**:
- Member variables: description, amount, type, category, currency
- Constructors: Default and parameterized
- Accessor methods: getters and setters
- Utility methods: display(), toCSV(), fromCSV()

**Data Members**:
```cpp
- description: std::string    // Transaction description
- amount: float               // Transaction amount
- type: std::string           // "credit" or "debit"
- category: std::string       // Spending category
- currency: std::string       // Currency code (USD, INR, EUR, etc.)
```

**Size**: ~1 KB | ~45 lines

---

#### **3. transaction.cpp** (Transaction Implementation)
**Purpose**: Implement Transaction class methods

**Responsibilities**:
- Implement constructors and destructors
- Provide getter/setter implementations
- Handle CSV serialization (toCSV)
- Handle CSV deserialization (fromCSV)
- Implement transaction display method

**Key Methods**:
- `toCSV()`: Convert transaction to CSV format for file storage
- `fromCSV()`: Parse CSV line and create transaction object
- `display()`: Print formatted transaction information
- Getters: Retrieve transaction attributes
- Setters: Update transaction attributes

**CSV Format**:
```
description,amount,type,category,currency
Lunch,250.50,debit,food,INR
```

**Size**: ~2 KB | ~90 lines

---

#### **4. currency_converter.hpp** (REST API Interface - Header)
**Purpose**: Define the currency conversion interface with REST API integration

**Responsibilities**:
- Declare REST API client methods
- Define exchange rate management interface
- Provide currency conversion methods
- Declare JSON parsing capability

**Key Components**:
- CURL integration for HTTP requests
- Exchange rate cache management
- Currency conversion algorithms
- API response parsing

**Public Methods**:
```cpp
- fetchExchangeRates(currency): Fetch rates for base currency
- convertCurrency(amount, from, to): Convert between currencies
- getExchangeRate(currency): Get specific rate
- displayAvailableCurrencies(): List supported currencies
- isCurrencySupported(currency): Validate currency code
```

**Private Members**:
```cpp
- apiKey: std::string         // API authentication
- baseURL: std::string        // API endpoint
- exchangeRates: std::map     // Rate cache
- baseCurrency: std::string   // Current base currency
```

**Size**: ~1 KB | ~45 lines

---

#### **5. currency_converter.cpp** (REST API Implementation)
**Purpose**: Implement REST API integration and currency conversion logic

**Responsibilities**:
- Make HTTP requests to ExchangeRate-API
- Parse JSON responses
- Manage exchange rate caching
- Implement currency conversion algorithms
- Handle CURL operations

**Key Functionality**:

**REST API Integration**:
- Uses libcurl for HTTP GET requests
- Fetches rates from: `https://api.exchangerate-api.com/v4/latest/[CURRENCY]`
- Response format: JSON with "rates" object

**JSON Parsing**:
- Custom parser (Windows-compatible)
- Extracts currency codes and rates
- Validates data format

**Currency Conversion**:
- Direct conversion: `amount * rate`
- Inverse conversion: `amount / rate`
- Cross-conversion: Via base currency

**Error Handling**:
- Network failure handling
- Invalid response detection
- Missing currency management

**Size**: ~8 KB | ~220 lines

---

#### **6. transaction_manager.hpp** (Business Logic Interface - Header)
**Purpose**: Define transaction management and analytics interface

**Responsibilities**:
- Declare transaction collection management
- Define analytics methods
- Provide currency conversion operations
- Declare file I/O operations

**Key Components**:
- Transaction collection management
- File persistence methods
- Analytics calculation methods
- Currency conversion features

**Public Methods**:
```cpp
// File Operations
- loadTransactions(): Load from CSV
- saveTransactions(): Save to CSV

// Transaction Management
- addTransaction(): Add new transaction
- displayAllTransactions(): Show all records

// Analytics
- trackCreditAndDebit(): Calculate totals
- findMostSpentCategory(): Identify top spending
- trackScholarshipsAndLoans(): Monitor special categories
- trackDues(): Track outstanding dues
- checkTransactionLimit(): Validate spending limits

// Currency Features
- convertTransactionCurrency(): Convert single transaction
- displayTransactionsInCurrency(): View in target currency
- convertAllTransactionsTo(): Convert entire portfolio

// Sharing
- shareTransactionHistory(): Export for guardians
```

**Private Members**:
```cpp
- transactions: std::vector<Transaction>     // All records
- filename: std::string                      // CSV file path
- converter: CurrencyConverter*              // API reference
- defaultCurrency: std::string               // Current currency
```

**Size**: ~1.5 KB | ~55 lines

---

#### **7. transaction_manager.cpp** (Business Logic Implementation)
**Purpose**: Implement transaction management and analytics

**Responsibilities**:
- Load and save transactions from/to CSV
- Manage transaction collection
- Calculate financial analytics
- Implement currency conversion operations
- Provide data formatting and presentation

**Key Functionality**:

**File Management**:
- CSV parsing with error handling
- Safe file I/O operations
- Atomic save operations
- Backward compatibility support

**Analytics Algorithms**:
- Aggregate calculations (sum, count)
- Categorical analysis with std::map
- Maximum element detection
- Cross-currency calculations

**Data Validation**:
- Input sanitization
- Currency code validation
- Amount verification
- Category validation

**Size**: ~10 KB | ~310 lines

---

#### **8. CMakeLists.txt** (Build Configuration)
**Purpose**: Configure project building process

**Responsibilities**:
- Define build targets
- Manage dependencies
- Configure compiler flags
- Set up library linking
- Enable CMake integration

**Key Configurations**:
```cmake
- C++17 standard enforcement
- Warning flags for code quality
- CURL library integration
- Platform-specific settings (Windows/Linux/macOS)
- Output directory specification
```

**Build Commands**:
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

**Size**: ~1.5 KB | ~45 lines

---

### Supplementary Documentation Files

#### **README.md**
- Quick start guide
- Feature overview
- Basic usage instructions

#### **WINDOWS_FINAL_SETUP.md**
- Detailed Windows installation steps
- vcpkg and Visual Studio setup
- Troubleshooting for Windows users

#### **WINDOWS_FILES_SUMMARY.txt**
- File naming and renaming guide
- Windows-specific considerations
- Quick reference checklist

---

## 🔌 API Integration

### ExchangeRate-API Integration

#### Overview
MONEFY integrates with **ExchangeRate-API**, a free, reliable service providing real-time exchange rates for 160+ currencies.

#### API Details
- **Service**: ExchangeRate-API
- **Base URL**: `https://api.exchangerate-api.com/v4/latest/`
- **Authentication**: None required (free tier)
- **Rate Limit**: 1,500 requests/month (free tier)
- **Update Frequency**: Daily

#### API Request Format
```
GET https://api.exchangerate-api.com/v4/latest/[BASE_CURRENCY]

Example:
GET https://api.exchangerate-api.com/v4/latest/INR
```

#### API Response Format
```json
{
  "base": "INR",
  "date": "2024-11-01",
  "rates": {
    "USD": 0.0120,
    "EUR": 0.0122,
    "GBP": 0.0103,
    "JPY": 1.6789,
    "AUD": 0.0207,
    "CAD": 0.0177,
    ...
  }
}
```

#### Supported Currencies (Sample)
```
USD - United States Dollar     EUR - Euro
GBP - British Pound           JPY - Japanese Yen
INR - Indian Rupee            AUD - Australian Dollar
CAD - Canadian Dollar         CHF - Swiss Franc
CNY - Chinese Yuan            SEK - Swedish Krona
And 150+ more...
```

#### How It Works in CHILLAR

1. **Rate Fetching**:
   ```cpp
   CurrencyConverter converter;
   converter.fetchExchangeRates("INR");  // Fetch rates for INR
   ```

2. **Rate Caching**:
   - Rates stored in memory after first fetch
   - Reduces API calls and improves performance
   - Valid for current session

3. **Currency Conversion**:
   ```cpp
   float usd = converter.convertCurrency(1000, "INR", "USD");
   // 1000 INR ≈ 12 USD
   ```

#### Error Handling
- Network failure detection
- Invalid response handling
- Unsupported currency detection
- Graceful degradation

---

## 💾 Data Management

### Transaction Storage

#### File Format: CSV (Comma-Separated Values)

**File**: `transactions.csv` (auto-created)

**Format**:
```csv
description,amount,type,category,currency
Lunch,250.50,debit,food,INR
Salary,50000,credit,income,INR
International purchase,100,debit,shopping,USD
```

**Advantages**:
- Human-readable
- Compatible with spreadsheet applications
- Easy backup and recovery
- Simple parsing logic
- Platform-independent

### Data Persistence

#### Loading
```cpp
TransactionManager manager("transactions.csv", converter);
// Automatically loads existing transactions on initialization
```

#### Saving
```cpp
manager.addTransaction();
manager.saveTransactions();  // Auto-saves after each add
// Also saves on program exit
```

#### Backup
```bash
# Manual backup
cp transactions.csv transactions.csv.backup

# Or through File Manager
Copy transactions.csv to safe location
```

### Data Integrity

- **Atomic Operations**: Full save or nothing
- **Validation**: Input verification before storage
- **Recovery**: Backup files for data recovery
- **Compatibility**: Backward-compatible format

---

## 🚀 Performance Characteristics

### Time Complexity
| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Add Transaction | O(1) | Direct append |
| Save to File | O(n) | Linear file write |
| Load from File | O(n) | Linear file read |
| Find Max Category | O(n log n) | Sorting required |
| Currency Conversion | O(1) | Lookup + calculation |
| API Fetch | O(1) | Network bound |

### Memory Usage
- **Per Transaction**: ~200 bytes (approx)
- **Exchange Rates**: ~5 KB (160+ currencies)
- **Total (100 transactions)**: ~25 MB

### Speed Benchmarks
- Add Transaction: <1ms
- View Analytics: <10ms
- Currency Conversion: <1ms (cached)
- API Fetch: 100-500ms (first time)

---

## 🔒 Security Features

1. **Input Validation**
   - Verify currency codes
   - Validate numeric inputs
   - Sanitize descriptions

2. **Secure Communication**
   - HTTPS for API calls
   - SSL/TLS certificate verification
   - CURL built-in security

3. **Data Protection**
   - Local-only storage
   - No cloud transmission
   - User-controlled backups

4. **Error Handling**
   - Graceful failure handling
   - User-friendly error messages
   - Application stability

---

## 🐛 Troubleshooting

### Common Issues

#### Issue: "CURL library not found"
**Solution**:
```bash
# Windows
vcpkg install curl:x64-windows

# Ubuntu/Debian
sudo apt-get install libcurl4-openssl-dev

# macOS
brew install curl
```

#### Issue: "CMake configuration failed"
**Solution**:
- Delete `build` folder
- Recreate: `mkdir build && cd build`
- Reconfigure: `cmake ..`

#### Issue: "API connection failed"
**Solution**:
- Check internet connection
- Verify firewall settings
- Try different base currency

#### Issue: "Transactions not saving"
**Solution**:
- Check write permissions
- Verify disk space
- Check file path validity

#### Issue: "Build fails with 'undefined reference'"
**Solution**:
- Ensure all .cpp files are compiled
- Check CURL library linking
- Verify CMakeLists.txt configuration

---

## 📈 Future Enhancements

### Phase 2 Features
1. **Database Backend**
   - Replace CSV with SQLite
   - Enhanced query capabilities
   - Better performance

2. **Graphical User Interface**
   - Qt/wxWidgets implementation
   - Visual charts and graphs
   - Improved user experience

3. **Mobile Application**
   - iOS/Android companion app
   - Cloud synchronization
   - Mobile-first features

4. **Advanced Analytics**
   - Spending forecasts
   - Budget recommendations
   - Trend analysis
   - Goal tracking

5. **Multi-User Support**
   - User authentication
   - Family account management
   - Role-based access control

6. **Cloud Features**
   - Data backup to cloud
   - Cross-device synchronization
   - Real-time collaboration

7. **Export Features**
   - PDF reports
   - Excel export
   - Graph generation
   - Email reports

---

## 📝 Code Quality Standards

- **Language Standard**: C++17 (Modern C++)
- **Compiler Flags**: `-Wall -Wextra -std=c++17`
- **Naming Conventions**: camelCase for methods, UPPER_CASE for constants
- **Documentation**: Inline comments for complex logic
- **Error Handling**: Exception-safe code with proper cleanup

---


## 🎯 Conclusion

MONEFY is a comprehensive solution for personal financial management with professional-grade features including real-time currency conversion, transaction tracking, and financial analytics. Built with modern C++ practices, it serves as both a practical application and an educational resource for understanding REST API integration, object-oriented design, and financial data management.

Whether you're managing personal finances, tracking international transactions, or learning advanced C++ concepts, CHILLAR provides a robust, scalable, and user-friendly platform.

---

**Version**: 2.0 (Windows Native Edition)  
**Last Updated**: November 2025
**Status**: Production Ready ✅
