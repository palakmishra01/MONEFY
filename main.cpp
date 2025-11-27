#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "transaction_manager.hpp"
#include "currency_converter.hpp"

class MonefyApp {
private:
    TransactionManager* transactionManager;
    CurrencyConverter* currencyConverter;
    std::string baseCurrency;

    void displayMainMenu() {
        std::cout << "\n";
        std::cout << "**************************************************************\n";
        std::cout << "Select the function which you want to perform:\n";
        std::cout << "1.  Add Transactions\n";
        std::cout << "2.  Display total credited and debited\n";
        std::cout << "3.  Find where you spent the most money\n";
        std::cout << "4.  Track Scholarships and Loans\n";
        std::cout << "5.  Track dues\n";
        std::cout << "6.  Share transaction history with Guardian\n";
        std::cout << "7.  Check transaction limit\n";
        std::cout << "8.  Currency Conversion Features\n";
        std::cout << "9.  Display all transactions\n";
        std::cout << "10. Exit\n";
        std::cout << "**************************************************************\n";
    }

    void displayCurrencyMenu() {
        std::cout << "\n";
        std::cout << "======== CURRENCY CONVERSION MENU ========\n";
        std::cout << "1. Display available currencies\n";
        std::cout << "2. Set base currency for exchange rates\n";
        std::cout << "3. Convert specific transaction\n";
        std::cout << "4. View all transactions in different currency\n";
        std::cout << "5. Convert all transactions to a currency\n";
        std::cout << "6. Back to main menu\n";
        std::cout << "==========================================\n";
    }

    void handleCurrencyConversion() {
        int choice;
        while (true) {
            displayCurrencyMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    currencyConverter->displayAvailableCurrencies();
                    break;

                case 2: {
                    std::string currency;
                    std::cout << "Enter base currency (e.g., INR, USD, EUR): ";
                    std::cin >> currency;
                    
                    // Convert to uppercase
                    std::transform(currency.begin(), currency.end(), currency.begin(), ::toupper);
                    
                    if (currencyConverter->fetchExchangeRates(currency)) {
                        baseCurrency = currency;
                        transactionManager->setDefaultCurrency(currency);
                        std::cout << "Base currency set to " << currency << std::endl;
                    } else {
                        std::cerr << "Failed to fetch rates for " << currency << std::endl;
                    }
                    break;
                }

                case 3: {
                    transactionManager->displayAllTransactions();
                    int index;
                    std::cout << "Enter transaction index to convert: ";
                    std::cin >> index;
                    
                    std::string targetCurrency;
                    std::cout << "Enter target currency: ";
                    std::cin >> targetCurrency;
                    std::transform(targetCurrency.begin(), targetCurrency.end(), 
                                 targetCurrency.begin(), ::toupper);
                    
                    transactionManager->convertTransactionCurrency(index - 1, targetCurrency);
                    break;
                }

                case 4: {
                    std::string currency;
                    std::cout << "Enter currency to view transactions in: ";
                    std::cin >> currency;
                    std::transform(currency.begin(), currency.end(), currency.begin(), ::toupper);
                    transactionManager->displayTransactionsInCurrency(currency);
                    break;
                }

                case 5: {
                    std::string currency;
                    std::cout << "Enter target currency: ";
                    std::cin >> currency;
                    std::transform(currency.begin(), currency.end(), currency.begin(), ::toupper);
                    transactionManager->convertAllTransactionsTo(currency);
                    break;
                }

                case 6:
                    return;

                default:
                    std::cout << "Invalid choice! Please try again." << std::endl;
            }
        }
    }

public:
    MonefyApp() : baseCurrency("INR") {
        currencyConverter = new CurrencyConverter("");
        transactionManager = new TransactionManager("transactions.csv", currencyConverter);
        
        // Initialize with default currency
        std::cout << "Initializing exchange rates for INR..." << std::endl;
        if (currencyConverter->fetchExchangeRates("INR")) {
            std::cout << "Ready to use!" << std::endl;
        }
    }

    void run() {
        std::cout << "\n";
        std::cout << "========================================\n";
        std::cout << "    WELCOME TO MONEFY!                \n";
        std::cout << "  Your personal account manager       \n";
        std::cout << "   Now with Currency Conversion!      \n";
        std::cout << "========================================\n";

        int choice;
        while (true) {
            displayMainMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    transactionManager->addTransaction();
                    break;

                case 2:
                    transactionManager->trackCreditAndDebit();
                    break;

                case 3:
                    transactionManager->findMostSpentCategory();
                    break;

                case 4:
                    transactionManager->trackScholarshipsAndLoans();
                    break;

                case 5:
                    transactionManager->trackDues();
                    break;

                case 6: {
                    std::string guardianName;
                    std::cout << "Enter guardian name: ";
                    std::cin.ignore();
                    std::getline(std::cin, guardianName);
                    transactionManager->shareTransactionHistory(guardianName);
                    break;
                }

                case 7: {
                    float limit;
                    std::cout << "Enter transaction limit to check against: ";
                    std::cin >> limit;
                    transactionManager->checkTransactionLimit(limit);
                    break;
                }

                case 8:
                    handleCurrencyConversion();
                    break;

                case 9:
                    transactionManager->displayAllTransactions();
                    break;

                case 10: {
                    std::cout << "\n";
                    std::cout << "========================================\n";
                    std::cout << "Thank you for using Monefy!\n";
                    std::cout << "========================================\n";
                    std::cout << "\n";
                    return;
                }

                default:
                    std::cout << "Invalid choice! Please try again." << std::endl;
            }
        }
    }

    ~MonefyApp() {
        delete transactionManager;
        delete currencyConverter;
    }
};

int main() {
    MonefyApp app;
    app.run();
    return 0;
}