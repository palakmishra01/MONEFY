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
        std::cout << "1. Add Transactions\n";
        std::cout << "2. Display total credited and debited\n";
        std::cout << "3. Find where you spent the most money\n";
        std::cout << "4. Track dues\n";
        std::cout << "5. Check transaction limit\n";
        std::cout << "6. Exit\n";
        std::cout << "**************************************************************\n";
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
                    transactionManager->trackDues();
                    break;

                case 5: {
                    float limit;
                    std::cout << "Enter transaction limit to check against: ";
                    std::cin >> limit;
                    transactionManager->checkTransactionLimit(limit);
                    break;
                }

                case 6: {
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