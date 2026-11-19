#include "UIUtils.h"
#include "Vehicle.h"
#include "Customer.h"
#include "Rental.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

void UIUtils::clearScreen() {
    // Cross-platform screen clear: ANSI escape sequence with fallback
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        // ANSI escape code to clear screen and move cursor to home position
        cout << "\033[2J\033[1;1H" << flush;
    #endif
}

void UIUtils::printSeparator(char ch, int width) {
    cout << string(width, ch) << endl;
}

void UIUtils::printDoubleSeparator(int width) {
    printSeparator('=', width);
}

void UIUtils::printHeader(const string& title) {
    const int width = 55;
    printDoubleSeparator(width);
    int pad = (width - static_cast<int>(title.length())) / 2;
    if (pad < 0) pad = 0;
    cout << string(pad, ' ') << title << endl;
    printDoubleSeparator(width);
}

void UIUtils::printSubHeader(const string& title) {
    const int width = 55;
    printSeparator('-', width);
    cout << "  " << title << endl;
    printSeparator('-', width);
}

void UIUtils::printSuccess(const string& msg) {
    cout << "\n[SUCCESS] " << msg << "\n" << endl;
}

void UIUtils::printError(const string& msg) {
    cout << "\n[ERROR] " << msg << "\n" << endl;
}

void UIUtils::printWarning(const string& msg) {
    cout << "\n[WARNING] " << msg << "\n" << endl;
}

void UIUtils::printInfo(const string& msg) {
    cout << "\n[INFO] " << msg << "\n" << endl;
}

void UIUtils::pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.clear();
    // Clear any leftover characters up to newline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int UIUtils::getMenuChoice(int min, int max) {
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        if (cin >> choice) {
            if (choice >= min && choice <= max) {
                // Clear input buffer up to newline
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return choice;
            }
            cout << "Invalid choice! Please enter a number between " << min << " and " << max << ".\n";
        } else {
            cout << "Invalid input! Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string UIUtils::getStringInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        // Trim leading and trailing whitespace
        size_t start = input.find_first_not_of(" \t\r\n");
        size_t end = input.find_last_not_of(" \t\r\n");
        if (start != string::npos && end != string::npos) {
            return input.substr(start, end - start + 1);
        }
        cout << "Input cannot be empty. Please try again.\n";
    }
}

int UIUtils::getIntInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= min && value <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            cout << "Value must be between " << min << " and " << max << ".\n";
        } else {
            cout << "Invalid input! Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double UIUtils::getDoubleInput(const string& prompt, double min) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= min) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            cout << "Value must be at least " << min << ".\n";
        } else {
            cout << "Invalid input! Please enter a valid decimal number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

bool UIUtils::getConfirmation(const string& prompt) {
    while (true) {
        cout << prompt << " (Y/N): ";
        string resp;
        getline(cin, resp);
        if (!resp.empty()) {
            char c = toupper(static_cast<unsigned char>(resp[0]));
            if (c == 'Y') return true;
            if (c == 'N') return false;
        }
        cout << "Please enter 'Y' or 'N'.\n";
    }
}

void UIUtils::printVehicleTableHeader() {
    cout << "+----------+------------------+------------------+--------+-------------+-----------+" << endl;
    cout << "| " << left << setw(8) << "ID"
         << " | " << left << setw(16) << "Brand"
         << " | " << left << setw(16) << "Model"
         << " | " << left << setw(6)  << "Type"
         << " | " << left << setw(11) << "Price/Day"
         << " | " << left << setw(9)  << "Status"
         << " |" << endl;
    cout << "+----------+------------------+------------------+--------+-------------+-----------+" << endl;
}

void UIUtils::printVehicleTableRow(const Vehicle& v) {
    ostringstream priceStream;
    priceStream << "Rs. " << fixed << setprecision(0) << v.getPricePerDay();
    string statusStr = v.isAvailable() ? "Available" : "Rented";

    cout << "| " << left << setw(8)  << v.getId()
         << " | " << left << setw(16) << v.getBrand().substr(0, 16)
         << " | " << left << setw(16) << v.getModel().substr(0, 16)
         << " | " << left << setw(6)  << v.getType()
         << " | " << left << setw(11) << priceStream.str()
         << " | " << left << setw(9)  << statusStr
         << " |" << endl;
}

void UIUtils::printVehicleTableFooter() {
    cout << "+----------+------------------+------------------+--------+-------------+-----------+" << endl;
}

void UIUtils::printVehicleTable(const vector<shared_ptr<Vehicle>>& vehicles) {
    if (vehicles.empty()) {
        cout << "\n[No vehicles to display]\n" << endl;
        return;
    }
    printVehicleTableHeader();
    for (const auto& v : vehicles) {
        if (v) {
            printVehicleTableRow(*v);
        }
    }
    printVehicleTableFooter();
}

void UIUtils::printCustomerTable(const vector<Customer>& customers) {
    if (customers.empty()) {
        cout << "\n[No customers registered yet]\n" << endl;
        return;
    }
    cout << "+----------+----------------------+---------------+--------------------------+---------------+" << endl;
    cout << "| " << left << setw(8)  << "ID"
         << " | " << left << setw(20) << "Name"
         << " | " << left << setw(13) << "Phone"
         << " | " << left << setw(24) << "Email"
         << " | " << left << setw(13) << "License No"
         << " |" << endl;
    cout << "+----------+----------------------+---------------+--------------------------+---------------+" << endl;

    for (const auto& c : customers) {
        cout << "| " << left << setw(8)  << c.getId()
             << " | " << left << setw(20) << c.getName().substr(0, 20)
             << " | " << left << setw(13) << c.getPhone().substr(0, 13)
             << " | " << left << setw(24) << c.getEmail().substr(0, 24)
             << " | " << left << setw(13) << c.getLicenseNumber().substr(0, 13)
             << " |" << endl;
    }
    cout << "+----------+----------------------+---------------+--------------------------+---------------+" << endl;
}

void UIUtils::printRentalTable(const vector<Rental>& rentals) {
    if (rentals.empty()) {
        cout << "\n[No rental records found]\n" << endl;
        return;
    }
    cout << "+----------+------------+------------+------+-------------+------------+------------+-----------+" << endl;
    cout << "| " << left << setw(8)  << "RentalID"
         << " | " << left << setw(10) << "Cust ID"
         << " | " << left << setw(10) << "Veh ID"
         << " | " << left << setw(4)  << "Days"
         << " | " << left << setw(11) << "Total Amt"
         << " | " << left << setw(10) << "Start Date"
         << " | " << left << setw(10) << "End Date"
         << " | " << left << setw(9)  << "Status"
         << " |" << endl;
    cout << "+----------+------------+------------+------+-------------+------------+------------+-----------+" << endl;

    for (const auto& r : rentals) {
        ostringstream amtStream;
        amtStream << "Rs. " << fixed << setprecision(0) << r.getTotalAmount();
        string statusStr = r.isReturned() ? "Returned" : "Active";

        cout << "| " << left << setw(8)  << r.getRentalId()
             << " | " << left << setw(10) << r.getCustomerId()
             << " | " << left << setw(10) << r.getVehicleId()
             << " | " << left << setw(4)  << r.getDays()
             << " | " << left << setw(11) << amtStream.str()
             << " | " << left << setw(10) << r.getStartDate()
             << " | " << left << setw(10) << r.getEndDate()
             << " | " << left << setw(9)  << statusStr
             << " |" << endl;
    }
    cout << "+----------+------------+------------+------+-------------+------------+------------+-----------+" << endl;
}

void UIUtils::loadingAnimation(const string& msg, int durationMs) {
    cout << msg << flush;
    int steps = 5;
    int stepDuration = durationMs / steps;
    for (int i = 0; i < steps; ++i) {
        this_thread::sleep_for(chrono::milliseconds(stepDuration));
        cout << "." << flush;
    }
    cout << " Done!\n" << endl;
}

void UIUtils::printWelcomeScreen() {
    const int width = 55;
    printDoubleSeparator(width);
    cout << "       VEHICLE RENTAL MANAGEMENT SYSTEM" << endl;
    printDoubleSeparator(width);
    cout << "       Welcome to our Rental Service!" << endl;
    printDoubleSeparator(width);
    cout << "\n";
    cout << "  1. Admin Login\n";
    cout << "  2. Customer Registration\n";
    cout << "  3. Customer Login\n";
    cout << "  4. Exit\n\n";
    printSeparator('-', width);
}

