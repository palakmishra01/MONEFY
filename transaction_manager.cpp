#include "transaction_manager.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <iomanip>
#include <iostream>

TransactionManager::TransactionManager(const std::string& file, CurrencyConverter* curr)
    : filename(file), converter(curr), defaultCurrency("INR") {
    loadTransactions();
}

void TransactionManager::loadTransactions() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No existing transactions file. Starting fresh." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line) && transactions.size() < MAX_TRANSACTIONS) {
        if (!line.empty()) {
            transactions.push_back(Transaction::fromCSV(line));
        }
    }
    file.close();
    std::cout << "Loaded " << transactions.size() << " transactions" << std::endl;
}

void TransactionManager::saveTransactions() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing" << std::endl;
        return;
    }

    for (const auto& transaction : transactions) {
        file << transaction.toCSV() << std::endl;
    }
    file.close();
    std::cout << "Transactions saved successfully" << std::endl;
}

void TransactionManager::addTransaction() {
    if (transactions.size() >= MAX_TRANSACTIONS) {
        std::cerr << "Error: Maximum number of transactions reached." << std::endl;
        return;
    }

    std::string description, type, category, currency;
    float amount;

    std::cout << "Enter description: ";
    std::cin.ignore();
    std::getline(std::cin, description);

    std::cout << "Enter amount: ";
    std::cin >> amount;

    std::cout << "Enter type (credit/debit): ";
    std::cin >> type;

    std::cout << "Enter category: ";
    std::cin.ignore();
    std::getline(std::cin, category);

    std::cout << "Enter currency code (default INR): ";
    std::getline(std::cin, currency);

    if (currency.empty()) {
        currency = defaultCurrency;
    } else {
        // Convert to uppercase
        std::transform(currency.begin(), currency.end(), currency.begin(), ::toupper);
        if (!converter->isCurrencySupported(currency)) {
            std::cout << "Warning: Currency might not be supported. Using anyway." << std::endl;
        }
    }

    transactions.emplace_back(description, amount, type, category, currency);
    saveTransactions();

    std::cout << "Transaction added successfully!" << std::endl;
}

void TransactionManager::displayAllTransactions() const {
    if (transactions.empty()) {
        std::cout << "No transactions to display." << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "All Transactions:" << std::endl;
    std::cout << "================================================" << std::endl;

    for (size_t i = 0; i < transactions.size(); i++) {
        std::cout << i + 1 << ". ";
        transactions[i].display();
    }
    std::cout << "================================================" << std::endl;
    std::cout << std::endl;
}

void TransactionManager::trackCreditAndDebit() const {
    float totalCredit = 0.0f, totalDebit = 0.0f;

    for (const auto& transaction : transactions) {
        if (transaction.getType() == "credit") {
            totalCredit += transaction.getAmount();
        } else if (transaction.getType() == "debit") {
            totalDebit += transaction.getAmount();
        }
    }

    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Credit: " << totalCredit << " " << defaultCurrency << std::endl;
    std::cout << "Total Debit: " << totalDebit << " " << defaultCurrency << std::endl;
    std::cout << "Net Balance: " << (totalCredit - totalDebit) << " " << defaultCurrency << std::endl;
    std::cout << std::endl;
}

void TransactionManager::findMostSpentCategory() const {
    if (transactions.empty()) {
        std::cout << "No transactions found." << std::endl;
        return;
    }

    std::map<std::string, float> categorySpent;

    for (const auto& transaction : transactions) {
        if (transaction.getType() == "debit") {
            categorySpent[transaction.getCategory()] += transaction.getAmount();
        }
    }

    if (categorySpent.empty()) {
        std::cout << "No debit transactions found." << std::endl;
        return;
    }

    auto maxCategory = std::max_element(categorySpent.begin(), categorySpent.end(),
                                       [](const auto& a, const auto& b) {
                                           return a.second < b.second;
                                       });

    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Category with most spending: " << maxCategory->first 
              << " (" << maxCategory->second << " " << defaultCurrency << ")" << std::endl;
    std::cout << std::endl;
}

void TransactionManager::trackScholarshipsAndLoans() const {
    float totalScholarships = 0.0f, totalLoans = 0.0f;

    for (const auto& transaction : transactions) {
        if (transaction.getCategory() == "scholarship") {
            totalScholarships += transaction.getAmount();
        } else if (transaction.getCategory() == "loan") {
            totalLoans += transaction.getAmount();
        }
    }

    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Scholarships: " << totalScholarships << " " << defaultCurrency << std::endl;
    std::cout << "Total Loans: " << totalLoans << " " << defaultCurrency << std::endl;
    std::cout << std::endl;
}

void TransactionManager::trackDues() const {
    float totalDues = 0.0f;

    for (const auto& transaction : transactions) {
        if (transaction.getCategory() == "dues") {
            totalDues += transaction.getAmount();
        }
    }

    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Dues: " << totalDues << " " << defaultCurrency << std::endl;
    std::cout << std::endl;
}

void TransactionManager::checkTransactionLimit(float limit) const {
    bool exceeded = false;

    std::cout << std::endl;
    for (const auto& transaction : transactions) {
        if (transaction.getAmount() > limit) {
            std::cout << "Transaction '" << transaction.getDescription() 
                      << "' exceeds the limit: " << transaction.getAmount() 
                      << " " << transaction.getCurrency() << std::endl;
            exceeded = true;
        }
    }

    if (!exceeded) {
        std::cout << "No transactions exceed the limit of " << limit << std::endl;
    }
    std::cout << std::endl;
}

void TransactionManager::convertTransactionCurrency(int index, const std::string& targetCurrency) {
    if (index < 0 || index >= static_cast<int>(transactions.size())) {
        std::cerr << "Error: Invalid transaction index" << std::endl;
        return;
    }

    Transaction& trans = transactions[index];
    std::string fromCurrency = trans.getCurrency();

    float convertedAmount = converter->convertCurrency(trans.getAmount(), fromCurrency, targetCurrency);

    if (convertedAmount > 0) {
        std::cout << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << trans.getAmount() << " " << fromCurrency << " = " 
                  << convertedAmount << " " << targetCurrency << std::endl;
        std::cout << std::endl;
    }
}

void TransactionManager::displayTransactionsInCurrency(const std::string& targetCurrency) {
    if (transactions.empty()) {
        std::cout << "No transactions to display." << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "Transactions in " << targetCurrency << ":" << std::endl;
    std::cout << "================================================" << std::endl;

    for (size_t i = 0; i < transactions.size(); i++) {
        float convertedAmount = converter->convertCurrency(
            transactions[i].getAmount(),
            transactions[i].getCurrency(),
            targetCurrency
        );

        std::cout << i + 1 << ". " << transactions[i].getDescription() << ": "
                  << std::fixed << std::setprecision(2) << convertedAmount << " " << targetCurrency
                  << " (" << transactions[i].getType() << ") - " << transactions[i].getCategory() << std::endl;
    }
    std::cout << "================================================" << std::endl;
    std::cout << std::endl;
}

void TransactionManager::convertAllTransactionsTo(const std::string& targetCurrency) {
    float totalCredit = 0.0f, totalDebit = 0.0f;

    std::cout << std::endl;
    std::cout << "Converting all transactions to " << targetCurrency << "..." << std::endl;
    std::cout << std::endl;

    for (const auto& transaction : transactions) {
        float convertedAmount = converter->convertCurrency(
            transaction.getAmount(),
            transaction.getCurrency(),
            targetCurrency
        );

        if (transaction.getType() == "credit") {
            totalCredit += convertedAmount;
        } else if (transaction.getType() == "debit") {
            totalDebit += convertedAmount;
        }
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Credit: " << totalCredit << " " << targetCurrency << std::endl;
    std::cout << "Total Debit: " << totalDebit << " " << targetCurrency << std::endl;
    std::cout << "Net Balance: " << (totalCredit - totalDebit) << " " << targetCurrency << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << std::endl;
}

void TransactionManager::shareTransactionHistory(const std::string& guardianName) const {
    std::cout << std::endl;
    std::cout << "Sharing transaction history with " << guardianName << "..." << std::endl;
    std::cout << "================================================" << std::endl;

    for (const auto& transaction : transactions) {
        transaction.display();
    }
    std::cout << "================================================" << std::endl;
    std::cout << std::endl;
}

int TransactionManager::getTransactionCount() const {
    return transactions.size();
}

const std::vector<Transaction>& TransactionManager::getTransactions() const {
    return transactions;
}

void TransactionManager::setDefaultCurrency(const std::string& curr) {
    defaultCurrency = curr;
}

TransactionManager::~TransactionManager() {
    saveTransactions();
}