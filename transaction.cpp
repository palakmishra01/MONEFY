#include "transaction.hpp"
#include <sstream>
#include <iomanip>

// Constructor
Transaction::Transaction() 
    : description(""), amount(0.0f), type("debit"), category(""), currency("INR") {}

Transaction::Transaction(const std::string& desc, float amt, const std::string& typ, 
                         const std::string& cat, const std::string& curr)
    : description(desc), amount(amt), type(typ), category(cat), currency(curr) {}

// Getters
std::string Transaction::getDescription() const {
    return description;
}

float Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getType() const {
    return type;
}

std::string Transaction::getCategory() const {
    return category;
}

std::string Transaction::getCurrency() const {
    return currency;
}

// Setters
void Transaction::setDescription(const std::string& desc) {
    description = desc;
}

void Transaction::setAmount(float amt) {
    amount = amt;
}

void Transaction::setType(const std::string& typ) {
    type = typ;
}

void Transaction::setCategory(const std::string& cat) {
    category = cat;
}

void Transaction::setCurrency(const std::string& curr) {
    currency = curr;
}

// Display transaction
void Transaction::display() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << description << ": " << amount << " " << currency 
              << " (" << type << ") - " << category << std::endl;
}

// Convert to CSV format
std::string Transaction::toCSV() const {
    std::stringstream ss;
    ss << description << "," << amount << "," << type << "," << category << "," << currency;
    return ss.str();
}

// Create Transaction from CSV line
Transaction Transaction::fromCSV(const std::string& line) {
    std::stringstream ss(line);
    std::string desc, type, category, currency;
    float amount;
    char comma;

    ss >> std::getline(ss, desc, ',');
    ss >> amount >> comma;
    ss >> std::getline(ss, type, ',');
    ss >> std::getline(ss, category, ',');
    ss >> std::getline(ss, currency, ',');

    // Handle missing currency field (for backward compatibility)
    if (currency.empty()) {
        currency = "INR";
    }

    return Transaction(desc, amount, type, category, currency);
}