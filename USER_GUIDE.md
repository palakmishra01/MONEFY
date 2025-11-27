# Monefy User Guide

**Your Personal Transaction Tracker with Multi-Currency Support**

---

## Table of Contents

1. [Getting Started](#getting-started)
2. [Main Menu Features](#main-menu-features)
3. [Currency Conversion Features](#currency-conversion-features)
4. [Transaction Categories](#transaction-categories)
5. [Tips & Best Practices](#tips--best-practices)
6. [Troubleshooting](#troubleshooting)
7. [Data Management](#data-management)

---

## Getting Started

### First Run

When you start Monefy for the first time:

1. The application will initialize with INR (Indian Rupee) as the default currency
2. It will fetch current exchange rates from the internet
3. If `transactions.csv` doesn't exist, it will be created automatically

```
========================================
    WELCOME TO Monefy!
  Your personal account manager
   Now with Currency Conversion!
========================================
Initializing exchange rates for INR...
Ready to use!
```

### System Requirements

- **Operating System**: Windows 10/11, Linux, or macOS
- **Internet Connection**: Required for currency conversion features
- **Storage**: Minimal (transactions stored in CSV format)

---

## Main Menu Features

### 1. Add Transactions

**Purpose**: Record your income (credits) and expenses (debits)

**How to use**:
1. Select option `1` from the main menu
2. Follow the prompts:

```
Enter description: Grocery shopping
Enter amount: 1500
Enter type (credit/debit): debit
Enter category: food
Enter currency code (default INR): INR
```

**Tips**:
- Be descriptive with transaction names for better tracking
- Press Enter without typing to use default currency (INR)
- Currency codes are 3 letters (USD, EUR, GBP, etc.)

---

### 2. Display Total Credited and Debited

**Purpose**: See your overall financial summary

**What it shows**:
- Total amount credited (income)
- Total amount debited (expenses)
- Net balance (credits - debits)

**Example output**:
```
Total Credit: 50000.00 INR
Total Debit: 35000.00 INR
Net Balance: 15000.00 INR
```

---

### 3. Find Where You Spent the Most Money

**Purpose**: Identify your highest spending category

**What it shows**:
- Category where you spent the most
- Total amount spent in that category

**Example output**:
```
Category with most spending: food (12500.00 INR)
```

**Use case**: Budget planning and identifying areas to cut expenses

---

### 4. Track Scholarships and Loans

**Purpose**: Monitor financial aid and borrowed money

**What it shows**:
- Total scholarships received
- Total loans taken

**How to use**:
- When adding transactions, use category `scholarship` or `loan`
- Select option `4` to view totals

**Example output**:
```
Total Scholarships: 25000.00 INR
Total Loans: 10000.00 INR
```

---

### 5. Track Dues

**Purpose**: Monitor pending payments and dues

**What it shows**:
- Total amount in dues

**How to use**:
- When adding transactions, use category `dues`
- Select option `5` to view total

**Example output**:
```
Total Dues: 5000.00 INR
```

---

### 6. Share Transaction History with Guardian

**Purpose**: Generate a report to share with parents/guardians

**How to use**:
1. Select option `6`
2. Enter guardian name when prompted

**Output**: Displays all transactions with complete details

**Example**:
```
Enter guardian name: Mom

Sharing transaction history with Mom...
================================================
1. Grocery shopping: 1500.00 INR (debit) - food
2. Salary: 50000.00 INR (credit) - income
3. Movie tickets: 800.00 INR (debit) - entertainment
================================================
```

---

### 7. Check Transaction Limit

**Purpose**: Identify transactions exceeding a specific amount

**How to use**:
1. Select option `7`
2. Enter the limit amount

**Example**:
```
Enter transaction limit to check against: 5000

Transaction 'Laptop Purchase' exceeds the limit: 45000.00 INR
Transaction 'Rent Payment' exceeds the limit: 15000.00 INR
```

**Use case**:
- Monitor large expenses
- Set spending alerts
- Track high-value transactions

---

### 8. Currency Conversion Features

See dedicated section below

---

### 9. Display All Transactions

**Purpose**: View complete transaction history

**What it shows**:
- Numbered list of all transactions
- Description, amount, currency, type, and category for each

**Example**:
```
================================================
All Transactions:
================================================
1. Grocery shopping: 1500.00 INR (debit) - food
2. Salary: 50000.00 INR (credit) - income
3. Movie tickets: 800.00 INR (debit) - entertainment
================================================
```

---

### 10. Exit

Safely exits the application and saves all data

---

## Currency Conversion Features

Access these features by selecting option `8` from the main menu.

### Sub-Menu Options

```
======== CURRENCY CONVERSION MENU ========
1. Display available currencies
2. Set base currency for exchange rates
3. Convert specific transaction
4. View all transactions in different currency
5. Convert all transactions to a currency
6. Back to main menu
==========================================
```

---

### 1. Display Available Currencies

**Purpose**: View all supported currencies and their exchange rates

**What it shows**:
- Currency codes (USD, EUR, GBP, etc.)
- Current exchange rate relative to base currency
- Over 160+ currencies supported

**Example output**:
```
Available Currencies (Exchange rates to INR):
================================================
USD   : 0.0120
EUR   : 0.0110
GBP   : 0.0095
JPY   : 1.7850
AUD   : 0.0185
CAD   : 0.0165
================================================
```

---

### 2. Set Base Currency for Exchange Rates

**Purpose**: Change your default currency

**How to use**:
1. Select option `2`
2. Enter currency code (e.g., USD, EUR, GBP)
3. Application fetches latest exchange rates

**Example**:
```
Enter base currency (e.g., INR, USD, EUR): USD
Base currency set to USD
```

**When to use**:
- When traveling abroad
- When working with foreign currency
- For international students

---

### 3. Convert Specific Transaction

**Purpose**: Convert one transaction to a different currency

**How to use**:
1. Select option `3`
2. Enter transaction number from the list
3. Enter target currency code

**Example**:
```
Enter transaction index to convert: 1
Enter target currency: USD

1500.00 INR = 18.00 USD
```

---

### 4. View All Transactions in Different Currency

**Purpose**: Display your entire transaction history in a different currency

**How to use**:
1. Select option `4`
2. Enter target currency code

**Example**:
```
Enter currency to view transactions in: USD

================================================
Transactions in USD:
================================================
1. Grocery shopping: 18.00 USD (debit) - food
2. Salary: 600.00 USD (credit) - income
3. Movie tickets: 9.60 USD (debit) - entertainment
================================================
```

**Use case**:
- Planning trips abroad
- Comparing expenses with friends in other countries
- Understanding spending in familiar currency

---

### 5. Convert All Transactions to a Currency

**Purpose**: Get your financial summary in any currency

**How to use**:
1. Select option `5`
2. Enter target currency code

**Example**:
```
Enter target currency: USD

Converting all transactions to USD...

Total Credit: 600.00 USD
Total Debit: 420.00 USD
Net Balance: 180.00 USD
================================================
```

**Use case**:
- Financial planning for international travel
- Comparing finances across countries
- Investment analysis

---

## Transaction Categories

### Recommended Categories

Use these standard categories for better tracking:

| Category | Description | Type | Examples |
|----------|-------------|------|----------|
| `food` | Food & groceries | Debit | Groceries, restaurants, snacks |
| `transport` | Transportation | Debit | Bus, taxi, fuel, metro |
| `entertainment` | Entertainment | Debit | Movies, games, events |
| `education` | Educational expenses | Debit | Books, courses, fees |
| `health` | Healthcare | Debit/Credit | Medical bills, insurance |
| `rent` | Housing costs | Debit | Rent, maintenance |
| `utilities` | Utility bills | Debit | Electricity, water, internet |
| `shopping` | General shopping | Debit | Clothes, accessories |
| `income` | Regular income | Credit | Salary, wages |
| `scholarship` | Financial aid | Credit | Scholarships, grants |
| `loan` | Borrowed money | Credit | Personal loans, student loans |
| `dues` | Pending payments | Debit | Outstanding bills |
| `savings` | Savings deposits | Debit | Savings account transfers |
| `other` | Miscellaneous | Both | Other expenses/income |

---

## Tips & Best Practices

### Recording Transactions

1. **Be Consistent**: Use the same category names consistently
2. **Record Immediately**: Add transactions as they happen to avoid forgetting
3. **Use Descriptive Names**: "Grocery - Walmart" is better than just "Shopping"
4. **Include Currency**: Always specify currency for international transactions

### Currency Conversion

1. **Update Rates Regularly**: Set base currency daily for latest rates
2. **Internet Required**: Currency features need active internet connection
3. **Base Currency**: Keep your primary currency as base for accurate tracking

### Financial Management

1. **Review Weekly**: Check your spending patterns weekly
2. **Set Limits**: Use the transaction limit feature to monitor large expenses
3. **Track Categories**: Monitor which categories consume most of your budget
4. **Guardian Sharing**: Share monthly reports with parents for transparency

---

## Troubleshooting

### Common Issues

#### 1. "Failed to fetch exchange rates"

**Cause**: No internet connection or API service down

**Solution**:
- Check your internet connection
- Try again after a few minutes
- The app will work offline but without currency conversion

#### 2. "Currency not supported"

**Cause**: Invalid currency code entered

**Solution**:
- Use option 8→1 to see available currencies
- Use standard 3-letter codes (USD, EUR, GBP)
- Currency codes are case-insensitive

#### 3. "Unable to open file for writing"

**Cause**: File permission issues

**Solution**:
- Check if transactions.csv is read-only
- Ensure the directory has write permissions
- Close any programs that might have the CSV file open

#### 4. Application crashes on startup

**Cause**: Corrupted transactions.csv file

**Solution**:
- Backup transactions.csv
- Delete or fix malformed entries
- Restart the application

---

## Data Management

### Where is my data stored?

All transactions are stored in `transactions.csv` in the same directory as the application.

### CSV Format

```
description,amount,type,category,currency
```

**Example**:
```
Grocery shopping,1500.00,debit,food,INR
Salary,50000.00,credit,income,INR
Movie tickets,800.00,debit,entertainment,INR
```

### Backup Your Data

**Important**: Always backup your `transactions.csv` file!

**How to backup**:
1. Copy `transactions.csv` to a safe location
2. Consider using cloud storage (Google Drive, OneDrive)
3. Keep regular backups (weekly recommended)

### Import/Export

**Export**: Simply copy the `transactions.csv` file

**Import**:
1. Ensure CSV follows the format above
2. Replace `transactions.csv` with your file
3. Restart Monefy

### Manual Editing

You can edit `transactions.csv` directly with any text editor or Excel:

1. Open `transactions.csv`
2. Edit entries (maintain CSV format)
3. Save file
4. Restart Monefy to see changes

**Warning**: Incorrect formatting will cause errors!

---

## Example Workflow

### Scenario: Monthly Budget Tracking

1. **Start of Month**:
   - Add salary as credit transaction
   ```
   Description: Monthly Salary
   Amount: 50000
   Type: credit
   Category: income
   Currency: INR
   ```

2. **Throughout Month**:
   - Add all expenses immediately
   - Use consistent categories

3. **End of Month**:
   - Use option 2 to see total credit/debit
   - Use option 3 to identify highest spending category
   - Use option 6 to share report with guardian
   - Analyze spending patterns for next month

### Scenario: International Trip Planning

1. **Before Trip**:
   - Set base currency to destination currency (option 8→2)
   - View all transactions in destination currency (option 8→4)
   - Plan budget based on converted amounts

2. **During Trip**:
   - Record expenses in local currency
   - Use multi-currency tracking

3. **After Trip**:
   - Convert all to home currency for total expense (option 8→5)
   - Analyze spending by category

---

## Need Help?

### Quick Reference Card

| Task | Menu Option | Steps |
|------|-------------|-------|
| Add transaction | 1 | Enter details when prompted |
| View balance | 2 | Automatic display |
| Check spending | 3 | Shows top category |
| Currency list | 8→1 | Display available currencies |
| Change currency | 8→2 | Enter new currency code |
| View in USD | 8→4 | Enter USD when prompted |
| Full report | 9 | Displays all transactions |

---

## Support

For issues or questions:
- Check this guide first
- Review WINDOWS_SETUP.md for installation issues
- Review README.md for technical details
- Check transactions.csv for data integrity

---

**Thank you for using Monefy!**

*Track Smart, Spend Wise!*
