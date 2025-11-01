#ifndef TRANSACTION_MANAGER_HPP
#define TRANSACTION_MANAGER_HPP

#include <vector>
#include <string>
#include "transaction.hpp"
#include "currency_converter.hpp"

class TransactionManager {
private:
    std::vector<Transaction> transactions;
    std::string filename;
    CurrencyConverter* converter;
    std::string defaultCurrency;

public:
    TransactionManager(const std::string& file, CurrencyConverter* curr);
    
    // File operations
    void loadTransactions();
    void saveTransactions();
    
    // Transaction management
    void addTransaction();
    void displayAllTransactions() const;
    
    // Analytics
    void trackCreditAndDebit() const;
    void findMostSpentCategory() const;
    void trackScholarshipsAndLoans() const;
    void trackDues() const;
    void checkTransactionLimit(float limit) const;
    
    // Currency conversion features
    void convertTransactionCurrency(int index, const std::string& targetCurrency);
    void displayTransactionsInCurrency(const std::string& targetCurrency);
    void convertAllTransactionsTo(const std::string& targetCurrency);
    
    // Sharing
    void shareTransactionHistory(const std::string& guardianName) const;
    
    // Getters
    int getTransactionCount() const;
    const std::vector<Transaction>& getTransactions() const;
    void setDefaultCurrency(const std::string& curr);
    
    ~TransactionManager();
};

#endif