//Programmer: Zhakfer Barmak
//Programmer's ID: 1846135

#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

class Expense {
public:
    string category;
    double amount;

    Expense(const string& cat, double amt) : category(cat), amount(amt) {}
};

class BSTNode {
public:
    Expense expense;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Expense& exp) : expense(exp), left(nullptr), right(nullptr) {}
};

class ExpenseTracker {
private:
    BSTNode* root;
    double monthlyBudget;

    void addExpense(BSTNode*& node, const string& category, double amount) {
        if (!node) {
            node = new BSTNode(Expense(category, amount));
            cout << "Expense added: " << category << " - $" << amount << endl;
        }
        else if (category < node->expense.category) {
            addExpense(node->left, category, amount);
        }
        else if (category > node->expense.category) {
            addExpense(node->right, category, amount);
        }
        else {
            // If category matches, just update the amount
            node->expense.amount += amount;
            cout << "Updated " << category << " - $" << node->expense.amount << endl;
        }
    }

    void inOrderTraversal(BSTNode* node) const {
        if (node) {
            inOrderTraversal(node->left);
            cout << node->expense.category << " - $" << node->expense.amount << endl;
            inOrderTraversal(node->right);
        }
    }

    double totalExpenses(BSTNode* node) const {
        if (!node) return 0;
        return node->expense.amount + totalExpenses(node->left) + totalExpenses(node->right);
    }

    void generateReport(BSTNode* node, map<string, double>& summary) const {
        if (node) {
            summary[node->expense.category] += node->expense.amount;
            generateReport(node->left, summary);
            generateReport(node->right, summary);
        }
    }

    void clearBST(BSTNode* node) {
        if (node) {
            clearBST(node->left);
            clearBST(node->right);
            delete node;
        }
    }

public:
    ExpenseTracker() : root(nullptr), monthlyBudget(0) {}

    ~ExpenseTracker() {
        clearBST(root);
    }

    void addExpense(const string& category, double amount) {
        addExpense(root, category, amount);
    }

    void setMonthlyBudget(double budget) {
        monthlyBudget = budget;
        cout << "Monthly budget set to $" << monthlyBudget << endl;
    }

    void viewExpenses() const {
        cout << "All Expenses:" << endl;
        inOrderTraversal(root);
    }

    double calculateTotalExpenses() const {
        return totalExpenses(root);
    }

    void generateReport() const {
        map<string, double> summary;
        generateReport(root, summary);
        cout << "Expense Report by Category:" << endl;
        for (const auto& pair : summary) {
            cout << pair.first << ": $" << pair.second << endl;
        }

    }

    void budgetStatus() const {
        double totalExpenses = calculateTotalExpenses();
        cout << "Total Expenses: $" << totalExpenses << endl;
        cout << "Monthly Budget: $" << monthlyBudget << endl;
        if (totalExpenses > monthlyBudget) {
            cout << "You are over your budget by $" << (totalExpenses - monthlyBudget) << "." << endl;
        }
        else {
            cout << "You have $" << (monthlyBudget - totalExpenses) << " remaining in your budget." << endl;
        }
    }
};

int main() {
    ExpenseTracker tracker;
    string command;

    cout << "Welcome to DVC Student Expense Tracker" << endl;
    cout << "Available commands: add, view, total, report, budget, status, quit" << endl;

    while (true) {
        cout << "Enter command: ";
        cin >> command;

        if (command == "add") {
            string category;
            double amount;
            cout << "Enter category and amount: ";
            cin >> category >> amount;
            tracker.addExpense(category, amount);
        }
        else if (command == "view") {
            tracker.viewExpenses();
        }
        else if (command == "total") {
            cout << "Total Expenses: $" << tracker.calculateTotalExpenses() << endl;
        }
        else if (command == "report") {
            tracker.generateReport();
        }
        else if (command == "budget") {
            double budget;
            cout << "Enter monthly budget: ";
            cin >> budget;
            tracker.setMonthlyBudget(budget);
        }
        else if (command == "status") {
            tracker.budgetStatus();
        }
        else if (command == "quit") {
            cout << "Exiting Expense Tracker." << endl;
            break;
        }
        else {
            cout << "Invalid command." << endl;
        }
    }

    return 0;
}
