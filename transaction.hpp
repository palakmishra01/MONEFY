#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <iostream>

#define MAX_TRANSACTIONS 100
#define MAX_DESC_LENGTH 50
#define MAX_NAME_LENGTH 50

class Transaction {
private:
    std::string description;
    float amount;
    std::string type;        // "credit" or "debit"
    std::string category;
    std::string currency;    // Currency code (USD, INR, EUR, etc.)

public:
    // Constructor
    Transaction();
    Transaction(const std::string& desc, float amt, const std::string& typ, 
                const std::string& cat, const std::string& curr = "INR");

    // Getters
    std::string getDescription() const;
    float getAmount() const;
    std::string getType() const;
    std::string getCategory() const;
    std::string getCurrency() const;

    // Setters
    void setDescription(const std::string& desc);
    void setAmount(float amt);
    void setType(const std::string& typ);
    void setCategory(const std::string& cat);
    void setCurrency(const std::string& curr);

    // Utility
    void display() const;
    std::string toCSV() const;
    static Transaction fromCSV(const std::string& line);
};

#endif