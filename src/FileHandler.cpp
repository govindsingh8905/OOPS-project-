#include "FileHandler.h"
#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"
#include "Customer.h"
#include "Rental.h"
#include "Payment.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <sys/stat.h>

using namespace std;

const string FileHandler::DATA_DIR = "data/";
const string FileHandler::VEHICLE_FILE = "data/vehicles.txt";
const string FileHandler::CUSTOMER_FILE = "data/customers.txt";
const string FileHandler::RENTAL_FILE = "data/rentals.txt";
const string FileHandler::PAYMENT_FILE = "data/payments.txt";

namespace {
    vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(str);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
}

void FileHandler::ensureDataDirectory() {
    try {
        error_code ec;
        filesystem::create_directories("data", ec);
    } catch (...) {
        // Fallback
        #if defined(_WIN32) || defined(_WIN64)
            system("mkdir data 2>nul");
        #else
            mkdir("data", 0777);
        #endif
    }
}

bool FileHandler::fileExists(const string& filename) {
    ifstream f(filename.c_str());
    return f.good();
}

void FileHandler::appendRecord(const string& filename, const string& record) {
    ensureDataDirectory();
    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        outFile << record << "\n";
    }
}

void FileHandler::appendRecord(const string& filename, const vector<string>& records) {
    ensureDataDirectory();
    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        for (const auto& rec : records) {
            outFile << rec << "\n";
        }
    }
}

void FileHandler::saveVehicles(const vector<shared_ptr<Vehicle>>& vehicles) {
    ensureDataDirectory();
    ofstream outFile(VEHICLE_FILE, ios::trunc);
    if (!outFile.is_open()) return;

    for (const auto& v : vehicles) {
        if (v) {
            outFile << v->serialize() << "\n";
        }
    }
}

vector<shared_ptr<Vehicle>> FileHandler::loadVehicles() {
    ensureDataDirectory();
    vector<shared_ptr<Vehicle>> vehicles;
    ifstream inFile(VEHICLE_FILE);
    if (!inFile.is_open()) return vehicles;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        vector<string> tokens = split(line, '|');
        // Minimum tokens needed is 8 for bike, 9 for car
        if (tokens.size() < 8) continue;

        try {
            string id = tokens[0];
            string brand = tokens[1];
            string model = tokens[2];
            double price = stod(tokens[3]);
            bool available = (tokens[4] == "1");
            string type = tokens[5];

            if (type == "Car" && tokens.size() >= 9) {
                int seats = stoi(tokens[6]);
                string fuelType = tokens[7];
                bool hasAC = (tokens[8] == "1");
                auto car = make_shared<Car>(id, brand, model, price, seats, fuelType, hasAC);
                car->setAvailable(available);
                vehicles.push_back(car);
            } else if (type == "Bike" && tokens.size() >= 8) {
                int cc = stoi(tokens[6]);
                string bikeType = tokens[7];
                auto bike = make_shared<Bike>(id, brand, model, price, cc, bikeType);
                bike->setAvailable(available);
                vehicles.push_back(bike);
            }
        } catch (const exception& e) {
            // Skip corrupted record
            continue;
        }
    }
    return vehicles;
}

void FileHandler::saveCustomers(const vector<Customer>& customers) {
    ensureDataDirectory();
    ofstream outFile(CUSTOMER_FILE, ios::trunc);
    if (!outFile.is_open()) return;

    for (const auto& c : customers) {
        outFile << c.serialize() << "\n";
    }
}

vector<Customer> FileHandler::loadCustomers() {
    ensureDataDirectory();
    vector<Customer> customers;
    ifstream inFile(CUSTOMER_FILE);
    if (!inFile.is_open()) return customers;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        vector<string> tokens = split(line, '|');
        if (tokens.size() < 6) continue;

        try {
            Customer c(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
            customers.push_back(c);
        } catch (...) {
            continue;
        }
    }
    return customers;
}

void FileHandler::saveRentals(const vector<Rental>& rentals) {
    ensureDataDirectory();
    ofstream outFile(RENTAL_FILE, ios::trunc);
    if (!outFile.is_open()) return;

    for (const auto& r : rentals) {
        outFile << r.serialize() << "\n";
    }
}

vector<Rental> FileHandler::loadRentals() {
    ensureDataDirectory();
    vector<Rental> rentals;
    ifstream inFile(RENTAL_FILE);
    if (!inFile.is_open()) return rentals;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        vector<string> tokens = split(line, '|');
        if (tokens.size() < 9) continue;

        try {
            string rentalId = tokens[0];
            string custId = tokens[1];
            string vehId = tokens[2];
            int days = stoi(tokens[3]);
            double amount = stod(tokens[4]);
            string startDate = tokens[5];
            string endDate = tokens[6];
            bool isReturned = (tokens[7] == "1");
            string returnDate = tokens[8];

            Rental r(rentalId, custId, vehId, days, amount, startDate, endDate);
            if (isReturned) {
                r.markReturned(returnDate);
            }
            rentals.push_back(r);
        } catch (...) {
            continue;
        }
    }
    return rentals;
}

void FileHandler::savePayments(const vector<Payment>& payments) {
    ensureDataDirectory();
    ofstream outFile(PAYMENT_FILE, ios::trunc);
    if (!outFile.is_open()) return;

    for (const auto& p : payments) {
        outFile << p.serialize() << "\n";
    }
}

vector<Payment> FileHandler::loadPayments() {
    ensureDataDirectory();
    vector<Payment> payments;
    ifstream inFile(PAYMENT_FILE);
    if (!inFile.is_open()) return payments;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        vector<string> tokens = split(line, '|');
        if (tokens.size() < 6) continue;

        try {
            string txnId = tokens[0];
            string rentalId = tokens[1];
            string custId = tokens[2];
            double amount = stod(tokens[3]);
            string method = tokens[4];
            string date = tokens[5];

            Payment p(txnId, rentalId, custId, amount, method, date);
            payments.push_back(p);
        } catch (...) {
            continue;
        }
    }
    return payments;
}

