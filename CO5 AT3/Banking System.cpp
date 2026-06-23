#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>

using namespace std;

// ==========================================
// 1. CUSTOM SYSTEM EXCEPTIONS
// ==========================================
class InsufficientFundsException : public runtime_error {
public:
    InsufficientFundsException(const string& msg) : runtime_error("Transaction Failed: " + msg) {}
};

class InvalidTransactionException : public runtime_error {
public:
    InvalidTransactionException(const string& msg) : runtime_error("Validation Error: " + msg) {}
};

// ==========================================
// 2. ABSTRACT BASE CLASS
// ==========================================
class BankAccount {
protected:
    string accountHolder;
    string accountNumber;
    double balance;

public:
    BankAccount(string holder, string accNum, double initialBalance) 
        : accountHolder(holder), accountNumber(accNum), balance(initialBalance) {
        if (initialBalance < 0) {
            throw InvalidTransactionException("Initial balance cannot be negative.");
        }
    }
    
    virtual ~BankAccount() {} // Virtual destructor for memory safety

    // Pure Virtual Function forcing specialized inheritance rules
    virtual string getAccountType() const = 0;

    // Virtual Functions enabling Runtime Polymorphism
    virtual void deposit(double amount) {
        if (amount <= 0) throw InvalidTransactionException("Deposit amount must be positive.");
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) throw InvalidTransactionException("Withdrawal amount must be positive.");
        if (amount > balance) throw InsufficientFundsException("Amount exceeds available balance.");
        balance -= amount;
    }

    void displaySummary() const {
        cout << "[" << left << setw(15) << getAccountType() << "] "
             << "Acc: " << setw(10) << accountNumber 
             << " | Holder: " << setw(15) << accountHolder 
             << " | Balance: INR " << fixed << setprecision(2) << balance << endl;
    }

    double getBalance() const { return balance; }
    string getAccNum() const { return accountNumber; }
};

// ==========================================
// 3. DERIVED CLASSES (Polymorphic Tiers)
// ==========================================
class SavingsAccount : public BankAccount {
private:
    double minBalanceBoundary;

public:
    SavingsAccount(string holder, string accNum, double initialBalance) 
        : BankAccount(holder, accNum, initialBalance), minBalanceBoundary(5000.0) {}

    string getAccountType() const override { return "Savings Tier"; }

    void withdraw(double amount) override {
        // Enforce strict regulatory minimum balance threshold
        if (balance - amount < minBalanceBoundary) {
            throw InsufficientFundsException("Operation denied. Savings accounts must maintain a minimum threshold of INR 5,000.");
        }
        BankAccount::withdraw(amount);
    }
};

class CurrentAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CurrentAccount(string holder, string accNum, double initialBalance) 
        : BankAccount(holder, accNum, initialBalance), overdraftLimit(25000.0) {}

    string getAccountType() const override { return "Current Tier"; }

    void withdraw(double amount) override {
        if (amount <= 0) throw InvalidTransactionException("Withdrawal amount must be positive.");
        // Allow withdrawal up to the balance + overdraft limit buffer
        if (amount > (balance + overdraftLimit)) {
            throw InsufficientFundsException("Operation denied. Transaction exceeds maximum authorized overdraft protection limit.");
        }
        balance -= amount;
    }
};

// ==========================================
// 4. INTERACTIVE TESTING SUITE (MAIN)
// ==========================================
int main() {
    // Standard raw pointers compatible with older compilers
    vector<BankAccount*> bankRegistry;

    // Seeding data directly into memory using standard 'new' keywords
    bankRegistry.push_back(new SavingsAccount("Arshiya Noor", "SAV-1001", 12000.0));
    bankRegistry.push_back(new CurrentAccount("Tech Corp", "CUR-2002", 50000.0));

    int choice = 0;
    while (true) {
        cout << "\n==================================================\n";
        cout << "         ROBUST POLYMORPHIC BANKING CORE          \n";
        cout << "==================================================\n";
        
        // Displaying current system state polymorphically
        cout << "\nCURRENT VAULT REGISTRY:\n";
        for (size_t i = 0; i < bankRegistry.size(); ++i) {
            bankRegistry[i]->displaySummary(); // Dynamic binding resolves perfectly
        }

        cout << "\nTRANSACTION MODULE:\n";
        cout << "1. Deposit to Savings (SAV-1001)\n";
        cout << "2. Withdraw from Savings (SAV-1001) - Test Min Balance Exception\n";
        cout << "3. Withdraw from Current (CUR-2002) - Test Overdraft Success\n";
        cout << "4. Withdraw from Current (CUR-2002) - Test Overdraft Failure Exception\n";
        cout << "5. Exit System\n";
        cout << "Select Test Case (1-5): ";
        cin >> choice;

        if (choice == 5) {
            cout << "\nShutting down vault engine, cleaning memory..." << endl;
            break;
        }

        // Processing selections under safe try-catch blocks
        try {
            switch (choice) {
                case 1:
                    cout << "\n[TEST CASE A: Standard Happy Path Deposit]" << endl;
                    bankRegistry[0]->deposit(3000.0);
                    cout << ">>> SUCCESS: Deposited INR 3000.00 cleanly into SAV-1001." << endl;
                    break;

                case 2:
                    cout << "\n[TEST CASE B: Balance Floor Violation Boundary]" << endl;
                    cout << "Attempting to withdraw INR 10,000.00 from SAV-1001..." << endl;
                    bankRegistry[0]->withdraw(10000.0); 
                    break;

                case 3:
                    cout << "\n[TEST CASE C: Authorized Overdraft Pipeline Limit]" << endl;
                    cout << "Attempting to withdraw INR 70,000.00 from CUR-2002 (Balance: 50k)..." << endl;
                    bankRegistry[1]->withdraw(70000.0);
                    cout << ">>> SUCCESS: Allowed via active Overdraft Protection configuration." << endl;
                    break;

                case 4:
                    cout << "\n[TEST CASE D: Overdraft Boundary Breach Failure Check]" << endl;
                    cout << "Attempting extreme withdrawal of INR 90,000.00 from CUR-2002..." << endl;
                    bankRegistry[1]->withdraw(90000.0);
                    break;

                default:
                    cout << "\nInvalid Selection. Try again." << endl;
            }
        }
        // Exception Handling captures errors without letting the engine crash
        catch (const InsufficientFundsException& e) {
            cout << "\n>>> CORE ENGINE INTERCEPTED EXCEPTION: " << e.what() << endl;
        }
        catch (const InvalidTransactionException& e) {
            cout << "\n>>> CORE ENGINE INTERCEPTED EXCEPTION: " << e.what() << endl;
        }

        // Pause to allow viewing console output in Dev-C++
        cout << "\nPress Enter to continue test suite...";
        cin.ignore();
        cin.get();
    }

    // Cleaning up allocated raw pointers manually to prevent memory leaks
    for (size_t i = 0; i < bankRegistry.size(); ++i) {
        delete bankRegistry[i];
    }

    return 0;
}
