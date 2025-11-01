#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

const int MAX_TRANSACTIONS = 100;

// Transaction class to encapsulate transaction data
class Transaction {
public:
    string description;
    float amount;
    string type; // "credit" or "debit"
    string category;

    Transaction() : amount(0.0f) {}
    
    Transaction(const string& desc, float amt, const string& t, const string& cat)
        : description(desc), amount(amt), type(t), category(cat) {}
};

// TransactionManager class to handle all operations
class TransactionManager {
private:
    vector<Transaction> transactions;
    string filename;

    void setColor(const string& color) {
        if (color == "red") cout << "\033[0;31m";
        else if (color == "green") cout << "\033[0;32m";
        else if (color == "yellow") cout << "\033[0;33m";
        else cout << "\033[0m";
    }

    void resetColor() {
        cout << "\033[0m";
    }

public:
    TransactionManager(const string& file) : filename(file) {}

    void addTransaction() {
        if (transactions.size() >= MAX_TRANSACTIONS) {
            setColor("red");
            cout << "Error: Maximum number of transactions reached.\n";
            resetColor();
            return;
        }

        Transaction t;
        setColor("green");
        
        cout << "Enter description: ";
        cin.ignore();
        getline(cin, t.description);

        cout << "Enter amount: ";
        cin >> t.amount;

        cout << "Enter type (credit/debit): ";
        cin >> t.type;

        cout << "Enter category: ";
        cin.ignore();
        getline(cin, t.category);

        transactions.push_back(t);
        cout << "Transaction added successfully!\n";
        resetColor();
    }

    void saveTransactionsToFile() {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Unable to open file for writing\n";
            return;
        }

        for (const auto& t : transactions) {
            file << t.description << "," << fixed << setprecision(2) << t.amount 
                 << "," << t.type << "," << t.category << "\n";
        }

        file.close();
        cout << "Transactions saved to " << filename << "\n";
    }

    void loadTransactions() {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Unable to open file (it may not exist yet)\n";
            return;
        }

        transactions.clear();
        string line;
        
        while (getline(file, line) && transactions.size() < MAX_TRANSACTIONS) {
            stringstream ss(line);
            Transaction t;
            
            getline(ss, t.description, ',');
            ss >> t.amount;
            ss.ignore(); // ignore comma
            getline(ss, t.type, ',');
            getline(ss, t.category);
            
            transactions.push_back(t);
        }

        file.close();
    }

    void trackCreditAndDebit() {
        float totalCredit = 0.0f, totalDebit = 0.0f;

        for (const auto& t : transactions) {
            if (t.type == "credit") {
                totalCredit += t.amount;
            } else if (t.type == "debit") {
                totalDebit += t.amount;
            }
        }

        cout << "Total Credit: " << fixed << setprecision(2) << totalCredit << "\n";
        cout << "Total Debit: " << fixed << setprecision(2) << totalDebit << "\n";
    }

    void findMostSpentCategory() {
        vector<string> categories;
        vector<float> categorySpent;

        for (const auto& t : transactions) {
            if (t.type == "debit") {
                bool found = false;
                for (size_t j = 0; j < categories.size(); j++) {
                    if (categories[j] == t.category) {
                        categorySpent[j] += t.amount;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    categories.push_back(t.category);
                    categorySpent.push_back(t.amount);
                }
            }
        }

        if (categories.empty()) {
            cout << "No debit transactions found.\n";
            return;
        }

        float maxSpent = 0.0f;
        string maxCategory;
        for (size_t i = 0; i < categories.size(); i++) {
            if (categorySpent[i] > maxSpent) {
                maxSpent = categorySpent[i];
                maxCategory = categories[i];
            }
        }

        cout << "Category with most spending: " << maxCategory 
             << " (" << fixed << setprecision(2) << maxSpent << ")\n";
    }

    void trackScholarshipsAndLoans() {
        float totalScholarships = 0.0f, totalLoans = 0.0f;

        for (const auto& t : transactions) {
            if (t.category == "scholarship") {
                totalScholarships += t.amount;
            } else if (t.category == "loan") {
                totalLoans += t.amount;
            }
        }

        cout << "Total Scholarships: " << fixed << setprecision(2) << totalScholarships << "\n";
        cout << "Total Loans: " << fixed << setprecision(2) << totalLoans << "\n";
    }

    void trackDues() {
        float totalDues = 0.0f;

        for (const auto& t : transactions) {
            if (t.category == "dues") {
                totalDues += t.amount;
            }
        }

        cout << "Total Dues: " << fixed << setprecision(2) << totalDues << "\n";
    }

    void shareTransactionHistory(const string& name) {
        cout << "Sharing transaction history with " << name << "...\n";
        for (const auto& t : transactions) {
            cout << t.description << ": " << fixed << setprecision(2) << t.amount 
                 << " (" << t.type << ") - " << t.category << "\n";
        }
    }

    void checkTransactionLimit(float limit) {
        for (const auto& t : transactions) {
            if (t.amount > limit) {
                cout << "Transaction '" << t.description << "' exceeds the limit: " 
                     << fixed << setprecision(2) << t.amount << "\n";
            }
        }
    }

    void displayMenu() {
        setColor("yellow");
        cout << "\n";
        setColor("green");
        cout << "Select the function which you want to perform according to their serial number\n";
        cout << "1. Add Transactions\n";
        cout << "2. Display total credited and debited\n";
        cout << "3. Find where you spent the most money.\n";
        cout << "4. Track Scholarships and Loans\n";
        cout << "5. Track dues\n";
        cout << "6. Add a Guardian\n";
        cout << "7. Check the transaction limit\n";
        cout << "8. exit\n";
        setColor("yellow");
        cout << "\n";
        resetColor();
    }
};

int main() {
    TransactionManager manager("transactions.csv");
    
    cout << "WELCOME TO CHILLAR!!!! \n";
    cout << "Your personal account manager. \n";
    
    int choice;
    
    while (true) {
        manager.displayMenu();
        cin >> choice;
        
        manager.loadTransactions();
        
        switch (choice) {
            case 1:
                manager.addTransaction();
                manager.saveTransactionsToFile();
                break;
            case 2:
                manager.trackCreditAndDebit();
                break;
            case 3:
                manager.findMostSpentCategory();
                break;
            case 4:
                manager.trackScholarshipsAndLoans();
                break;
            case 5:
                manager.trackDues();
                break;
            case 6: {
                string name;
                cout << "Enter the name of the family member/guardian to share transaction history: ";
                cin >> name;
                manager.shareTransactionHistory(name);
                break;
            }
            case 7: {
                float limit;
                cout << "Enter transaction limit to check against: ";
                cin >> limit;
                manager.checkTransactionLimit(limit);
                break;
            }
            case 8:
                cout << "Project created by: \n"
                     << "B24ME1002: Aarushi Singh\n"
                     << "B24ME1040: Krishna Mishra\n"
                     << "B24EE1050: Palak Mishra\n"
                     << "B24EE1080: Tanishka Trivedi\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}