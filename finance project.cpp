#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // for setprecision
#include <ctime>   // for date/time functions

using namespace std;

// Struct to represent a user
struct User {
    string username;
    string hashedPassword; // Store hashed password for security
    double balance;
    vector<string> transactions; // Store transaction details

    // Constructor
    User(string u, string p) : username(u), hashedPassword(hashFunction(p)), balance(0.0) {}

    // Example hash function (not secure, use a proper hashing library in practice)
    string hashFunction(string password) {
        // Implement a secure hash function here
        return password; // Placeholder example, not secure!
    }

    // Function to record a transaction
    void recordTransaction(double amount, bool isIncome, const string& description) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string date(dt); // Current date/time as a string

        // Record transaction details
        string type = (isIncome) ? "Income" : "Expense";
        string transactionDetail = type + " - $" + to_string(amount) + " - " + date + " - " + description;
        transactions.push_back(transactionDetail);

        // Update balance
        if (isIncome) {
            balance += amount;
        } else {
            balance -= amount;
        }
    }
};

vector<User> users; // Vector to store all users

// Function prototypes
void showMenu();
bool login();
void signup();
void recordTransaction(User& currentUser);
void viewBalance(const User& currentUser);
void generateReports(const User& currentUser);

// Function to display main menu options
void showMenu() {
    cout << "\n===== Main Menu =====" << endl;
    cout << "1. Record Income/Expense" << endl;
    cout << "2. View Balance" << endl;
    cout << "3. Generate Reports" << endl;
    cout << "4. Logout" << endl;
    cout << "======================" << endl;
}

// Function for user login
bool login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Find user in vector
    for (auto& user : users) {
        if (user.username == username && user.hashedPassword == user.hashFunction(password)) {
            cout << "Login successful!" << endl;
            return true;
        }
    }

    cout << "Invalid username or password." << endl;
    return false;
}

// Function for user signup
void signup() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    // Check if username already exists
    for (const auto& user : users) {
        if (user.username == username) {
            cout << "Username already exists. Please choose another username." << endl;
            return;
        }
    }

    cout << "Enter password: ";
    cin >> password;
    users.push_back(User(username, password));
    cout << "Signup successful!" << endl;
}

// Function to record a transaction
void recordTransaction(User& currentUser) {
    double amount;
    char type;
    string description;

    cout << "Enter transaction type (I for Income, E for Expense): ";
    cin >> type;
    cout << "Enter amount: ";
    cin >> amount;
    cout << "Enter description: ";
    cin.ignore(); // Ignore newline left in buffer
    getline(cin, description);

    bool isIncome = (type == 'I' || type == 'i');

    // Record transaction
    currentUser.recordTransaction(amount, isIncome, description);

    cout << "Transaction recorded successfully!" << endl;
}

// Function to view current balance
void viewBalance(const User& currentUser) {
    cout << fixed << setprecision(2);
    cout << "Current Balance: $" << currentUser.balance << endl;
}

// Function to generate reports (show transaction history)
void generateReports(const User& currentUser) {
    cout << "\n===== Transaction History =====" << endl;
    for (const auto& transaction : currentUser.transactions) {
        cout << transaction << endl;
    }
    cout << "===============================" << endl;
}

// Main function
int main() {
    int choice;
    bool loggedIn = false;
    User currentUser("", ""); // Placeholder user object

    while (true) {
        if (!loggedIn) {
            cout << "\nPlease login or signup." << endl;
            cout << "1. Login" << endl;
            cout << "2. Signup" << endl;
            cout << "3. Exit" << endl;
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    loggedIn = login();
                    break;
                case 2:
                    signup();
                    break;
                case 3:
                    return 0; // Exit program
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        } else {
            showMenu();
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    recordTransaction(currentUser);
                    break;
                case 2:
                    viewBalance(currentUser);
                    break;
                case 3:
                    generateReports(currentUser);
                    break;
                case 4:
                    loggedIn = false; // Logout
                    cout << "Logged out successfully." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }
    }

    return 0;
}
