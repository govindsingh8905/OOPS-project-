#include "RentalSystem.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

RentalSystem::RentalSystem() {
    FileHandler::ensureDataDirectory();
    loadAllData();
    seedDefaultDataIfEmpty();
}

RentalSystem::~RentalSystem() {
    saveAllData();
}

void RentalSystem::seedDefaultDataIfEmpty() {
    if (vehicles.empty()) {
        vehicles.push_back(make_shared<Car>("V101", "Tata", "Nexon", 1500.0, 5, "Petrol", true));
        vehicles.push_back(make_shared<Car>("V102", "Honda", "City", 2000.0, 5, "Petrol", true));
        vehicles.push_back(make_shared<Car>("V103", "Hyundai", "Creta", 2500.0, 5, "Diesel", true));
        vehicles.push_back(make_shared<Car>("V104", "Maruti", "Swift", 1200.0, 5, "Petrol", true));
        vehicles.push_back(make_shared<Car>("V105", "Toyota", "Fortuner", 4000.0, 7, "Diesel", true));

        vehicles.push_back(make_shared<Bike>("V106", "Royal Enfield", "Classic 350", 800.0, 350, "Cruiser"));
        vehicles.push_back(make_shared<Bike>("V107", "KTM", "Duke 200", 600.0, 200, "Sport"));
        vehicles.push_back(make_shared<Bike>("V108", "Honda", "Activa 6G", 350.0, 110, "Scooter"));
        vehicles.push_back(make_shared<Bike>("V109", "Yamaha", "R15 V4", 750.0, 155, "Sport"));
        vehicles.push_back(make_shared<Bike>("V110", "Bajaj", "Pulsar NS200", 500.0, 200, "Standard"));

        FileHandler::saveVehicles(vehicles);
    }

    if (customers.empty()) {
        customers.emplace_back("C1001", "Rahul Sharma", "9876543210", "rahul@email.com", "pass123", "DL1420110012345");
        customers.emplace_back("C1002", "Priya Singh", "9876543211", "priya@email.com", "pass456", "DL0420180098765");
        FileHandler::saveCustomers(customers);
    }
}

void RentalSystem::saveAllData() {
    FileHandler::saveVehicles(vehicles);
    FileHandler::saveCustomers(customers);
    FileHandler::saveRentals(rentals);
    FileHandler::savePayments(payments);
}

void RentalSystem::loadAllData() {
    vehicles = FileHandler::loadVehicles();
    customers = FileHandler::loadCustomers();
    rentals = FileHandler::loadRentals();
    payments = FileHandler::loadPayments();
}

string RentalSystem::getCurrentDate() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    ostringstream oss;
    oss << 1900 + ltm->tm_year << "-"
        << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
        << setfill('0') << setw(2) << ltm->tm_mday;
    return oss.str();
}

string RentalSystem::calculateEndDate(int daysFromNow) {
    time_t now = time(nullptr);
    now += static_cast<time_t>(daysFromNow) * 24 * 60 * 60;
    tm* ltm = localtime(&now);
    ostringstream oss;
    oss << 1900 + ltm->tm_year << "-"
        << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
        << setfill('0') << setw(2) << ltm->tm_mday;
    return oss.str();
}

string RentalSystem::generateVehicleId() {
    int maxNum = 100;
    for (const auto& v : vehicles) {
        string vid = v->getId();
        if (vid.length() > 1 && vid[0] == 'V') {
            try {
                int num = stoi(vid.substr(1));
                if (num > maxNum) maxNum = num;
            } catch (...) {}
        }
    }
    return "V" + to_string(maxNum + 1);
}

string RentalSystem::generateCustomerId() {
    int maxNum = 1000;
    for (const auto& c : customers) {
        string cid = c.getId();
        if (cid.length() > 1 && cid[0] == 'C') {
            try {
                int num = stoi(cid.substr(1));
                if (num > maxNum) maxNum = num;
            } catch (...) {}
        }
    }
    return "C" + to_string(maxNum + 1);
}

string RentalSystem::generateRentalId() {
    int maxNum = 1000;
    for (const auto& r : rentals) {
        string rid = r.getRentalId();
        if (rid.length() > 1 && rid[0] == 'R') {
            try {
                int num = stoi(rid.substr(1));
                if (num > maxNum) maxNum = num;
            } catch (...) {}
        }
    }
    return "R" + to_string(maxNum + 1);
}

string RentalSystem::generateTransactionId() {
    int maxNum = 1000;
    for (const auto& p : payments) {
        string tid = p.getTransactionId();
        if (tid.rfind("TXN", 0) == 0 && tid.length() > 3) {
            try {
                int num = stoi(tid.substr(3));
                if (num > maxNum) maxNum = num;
            } catch (...) {}
        }
    }
    return "TXN" + to_string(maxNum + 1);
}

shared_ptr<Vehicle> RentalSystem::findVehicleById(const string& id) {
    for (const auto& v : vehicles) {
        if (v && v->getId() == id) return v;
    }
    return nullptr;
}

Customer* RentalSystem::findCustomerById(const string& id) {
    for (auto& c : customers) {
        if (c.getId() == id) return &c;
    }
    return nullptr;
}

Customer* RentalSystem::findCustomerByEmail(const string& email) {
    for (auto& c : customers) {
        if (c.getEmail() == email) return &c;
    }
    return nullptr;
}

Rental* RentalSystem::findRentalById(const string& id) {
    for (auto& r : rentals) {
        if (r.getRentalId() == id) return &r;
    }
    return nullptr;
}

void RentalSystem::run() {
    bool running = true;
    while (running) {
        UIUtils::clearScreen();
        UIUtils::printWelcomeScreen();
        int choice = UIUtils::getMenuChoice(1, 4);

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                customerRegistration();
                break;
            case 3:
                customerLogin();
                break;
            case 4:
                UIUtils::printInfo("Thank you for using Vehicle Rental Management System! Goodbye.");
                running = false;
                break;
        }
    }
}

void RentalSystem::adminLogin() {
    UIUtils::clearScreen();
    UIUtils::printHeader("ADMIN LOGIN");
    string user = UIUtils::getStringInput("Enter Admin Username: ");
    string pwd = UIUtils::getStringInput("Enter Admin Password: ");

    if (admin.authenticate(user, pwd)) {
        UIUtils::loadingAnimation("Authenticating Admin", 500);
        UIUtils::printSuccess("Admin Login Successful!");
        adminDashboard();
    } else {
        UIUtils::printError("Invalid username or password! Access denied.");
        UIUtils::pressEnterToContinue();
    }
}

void RentalSystem::adminDashboard() {
    bool inDashboard = true;
    while (inDashboard) {
        UIUtils::clearScreen();
        UIUtils::printHeader("ADMIN DASHBOARD");
        cout << "  1. Add New Vehicle\n";
        cout << "  2. Remove Vehicle\n";
        cout << "  3. Update Vehicle Details\n";
        cout << "  4. View All Vehicles\n";
        cout << "  5. View Available Vehicles\n";
        cout << "  6. View Rented Vehicles\n";
        cout << "  7. View All Customers\n";
        cout << "  8. View All Rental Records\n";
        cout << "  9. View Revenue Report\n";
        cout << "  10. Logout\n";
        UIUtils::printSeparator('-', 55);

        int choice = UIUtils::getMenuChoice(1, 10);
        switch (choice) {
            case 1: addVehicle(); break;
            case 2: removeVehicle(); break;
            case 3: updateVehicle(); break;
            case 4: viewAllVehicles(); UIUtils::pressEnterToContinue(); break;
            case 5: viewAvailableVehicles(); UIUtils::pressEnterToContinue(); break;
            case 6: viewRentedVehicles(); UIUtils::pressEnterToContinue(); break;
            case 7: viewAllCustomers(); UIUtils::pressEnterToContinue(); break;
            case 8: viewAllRentals(); UIUtils::pressEnterToContinue(); break;
            case 9: viewRevenueReport(); UIUtils::pressEnterToContinue(); break;
            case 10:
                UIUtils::printInfo("Logged out of Admin successfully.");
                inDashboard = false;
                break;
        }
    }
}

void RentalSystem::addVehicle() {
    UIUtils::clearScreen();
    UIUtils::printHeader("ADD NEW VEHICLE");
    cout << "Select Vehicle Category:\n";
    cout << "  1. Car\n";
    cout << "  2. Bike\n";
    int typeChoice = UIUtils::getMenuChoice(1, 2);

    string brand = UIUtils::getStringInput("Enter Brand: ");
    string model = UIUtils::getStringInput("Enter Model: ");
    double price = UIUtils::getDoubleInput("Enter Rental Price Per Day (Rs.): ", 1.0);

    string newId = generateVehicleId();

    if (typeChoice == 1) {
        int seats = UIUtils::getIntInput("Enter Number of Seats (2-12): ", 2, 12);
        cout << "Select Fuel Type:\n";
        cout << "  1. Petrol\n  2. Diesel\n  3. Electric\n  4. CNG\n";
        int fuelChoice = UIUtils::getMenuChoice(1, 4);
        string fuelType = (fuelChoice == 1 ? "Petrol" : (fuelChoice == 2 ? "Diesel" : (fuelChoice == 3 ? "Electric" : "CNG")));
        bool hasAC = UIUtils::getConfirmation("Does the car have Air Conditioning?");

        vehicles.push_back(make_shared<Car>(newId, brand, model, price, seats, fuelType, hasAC));
    } else {
        int cc = UIUtils::getIntInput("Enter Engine Capacity in CC (50-2500): ", 50, 2500);
        cout << "Select Bike Type:\n";
        cout << "  1. Standard\n  2. Sport\n  3. Cruiser\n  4. Scooter\n";
        int bikeChoice = UIUtils::getMenuChoice(1, 4);
        string bikeType = (bikeChoice == 1 ? "Standard" : (bikeChoice == 2 ? "Sport" : (bikeChoice == 3 ? "Cruiser" : "Scooter")));

        vehicles.push_back(make_shared<Bike>(newId, brand, model, price, cc, bikeType));
    }

    saveAllData();
    UIUtils::printSuccess("Vehicle added successfully with ID: " + newId);
    UIUtils::pressEnterToContinue();
}

void RentalSystem::removeVehicle() {
    UIUtils::clearScreen();
    UIUtils::printHeader("REMOVE VEHICLE");
    UIUtils::printVehicleTable(vehicles);

    string vid = UIUtils::getStringInput("Enter Vehicle ID to remove: ");
    auto v = findVehicleById(vid);

    if (!v) {
        UIUtils::printError("Vehicle ID '" + vid + "' not found!");
        UIUtils::pressEnterToContinue();
        return;
    }

    if (!v->isAvailable()) {
        UIUtils::printError("Vehicle is currently rented! It cannot be removed until returned.");
        UIUtils::pressEnterToContinue();
        return;
    }

    cout << "\nVehicle to be removed:\n";
    cout << "  ID    : " << v->getId() << "\n";
    cout << "  Brand : " << v->getBrand() << "\n";
    cout << "  Model : " << v->getModel() << "\n";

    if (UIUtils::getConfirmation("Are you sure you want to permanently delete this vehicle?")) {
        vehicles.erase(remove_if(vehicles.begin(), vehicles.end(),
            [&vid](const shared_ptr<Vehicle>& ptr) { return ptr && ptr->getId() == vid; }),
            vehicles.end());
        saveAllData();
        UIUtils::printSuccess("Vehicle " + vid + " removed successfully!");
    } else {
        UIUtils::printInfo("Vehicle deletion cancelled.");
    }
    UIUtils::pressEnterToContinue();
}

void RentalSystem::updateVehicle() {
    UIUtils::clearScreen();
    UIUtils::printHeader("UPDATE VEHICLE DETAILS");
    UIUtils::printVehicleTable(vehicles);

    string vid = UIUtils::getStringInput("Enter Vehicle ID to update: ");
    auto v = findVehicleById(vid);

    if (!v) {
        UIUtils::printError("Vehicle ID '" + vid + "' not found!");
        UIUtils::pressEnterToContinue();
        return;
    }

    cout << "\nCurrent Vehicle Details:\n";
    cout << *v << endl;
    cout << "\nWhat would you like to update?\n";
    cout << "  1. Brand\n";
    cout << "  2. Model\n";
    cout << "  3. Rental Price Per Day\n";
    cout << "  4. Cancel\n";

    int choice = UIUtils::getMenuChoice(1, 4);
    if (choice == 1) {
        string brand = UIUtils::getStringInput("Enter New Brand: ");
        v->setBrand(brand);
        saveAllData();
        UIUtils::printSuccess("Vehicle brand updated successfully!");
    } else if (choice == 2) {
        string model = UIUtils::getStringInput("Enter New Model: ");
        v->setModel(model);
        saveAllData();
        UIUtils::printSuccess("Vehicle model updated successfully!");
    } else if (choice == 3) {
        double price = UIUtils::getDoubleInput("Enter New Price Per Day (Rs.): ", 1.0);
        v->setPricePerDay(price);
        saveAllData();
        UIUtils::printSuccess("Vehicle price updated successfully!");
    } else {
        UIUtils::printInfo("Update cancelled.");
    }
    UIUtils::pressEnterToContinue();
}

void RentalSystem::viewAllVehicles() {
    UIUtils::clearScreen();
    UIUtils::printHeader("ALL VEHICLES IN FLEET");
    UIUtils::printVehicleTable(vehicles);
}

void RentalSystem::viewAvailableVehicles() {
    UIUtils::clearScreen();
    UIUtils::printHeader("AVAILABLE VEHICLES FOR RENT");
    vector<shared_ptr<Vehicle>> availableVehicles;
    for (const auto& v : vehicles) {
        if (v && v->isAvailable()) {
            availableVehicles.push_back(v);
        }
    }
    UIUtils::printVehicleTable(availableVehicles);
}

void RentalSystem::viewRentedVehicles() {
    UIUtils::clearScreen();
    UIUtils::printHeader("CURRENTLY RENTED VEHICLES");
    vector<shared_ptr<Vehicle>> rentedVehicles;
    for (const auto& v : vehicles) {
        if (v && !v->isAvailable()) {
            rentedVehicles.push_back(v);
        }
    }
    UIUtils::printVehicleTable(rentedVehicles);
}

void RentalSystem::viewAllCustomers() {
    UIUtils::clearScreen();
    UIUtils::printHeader("REGISTERED CUSTOMERS");
    UIUtils::printCustomerTable(customers);
}

void RentalSystem::viewAllRentals() {
    UIUtils::clearScreen();
    UIUtils::printHeader("ALL RENTAL RECORDS");
    UIUtils::printRentalTable(rentals);
}

void RentalSystem::viewRevenueReport() {
    UIUtils::clearScreen();
    UIUtils::printHeader("REVENUE & PERFORMANCE REPORT");

    double totalRevenue = 0.0;
    for (const auto& p : payments) {
        totalRevenue += p.getAmount();
    }

    int totalBookings = static_cast<int>(rentals.size());
    int activeRentals = 0;
    int completedRentals = 0;

    for (const auto& r : rentals) {
        if (r.isReturned()) completedRentals++;
        else activeRentals++;
    }

    // Vehicle type breakdown
    int carRentals = 0;
    int bikeRentals = 0;
    double carRevenue = 0.0;
    double bikeRevenue = 0.0;

    for (const auto& r : rentals) {
        auto v = findVehicleById(r.getVehicleId());
        if (v) {
            if (v->getType() == "Car") {
                carRentals++;
                carRevenue += r.getTotalAmount();
            } else {
                bikeRentals++;
                bikeRevenue += r.getTotalAmount();
            }
        }
    }

    cout << "-------------------------------------------------------" << endl;
    cout << "  FINANCIAL SUMMARY" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "  Total Revenue Collected  : Rs. " << fixed << setprecision(2) << totalRevenue << endl;
    cout << "  Car Rentals Revenue      : Rs. " << fixed << setprecision(2) << carRevenue << endl;
    cout << "  Bike Rentals Revenue     : Rs. " << fixed << setprecision(2) << bikeRevenue << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "  BOOKING SUMMARY" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "  Total Bookings Made      : " << totalBookings << endl;
    cout << "  Active Rentals           : " << activeRentals << endl;
    cout << "  Completed / Returned     : " << completedRentals << endl;
    cout << "  Car Bookings             : " << carRentals << endl;
    cout << "  Bike Bookings            : " << bikeRentals << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "  FLEET UTILIZATION" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "  Total Vehicles in Fleet  : " << vehicles.size() << endl;
    cout << "  Vehicles Available       : " << (vehicles.size() - activeRentals) << endl;
    cout << "  Vehicles Currently Rented: " << activeRentals << endl;
    cout << "=======================================================" << endl;
}

void RentalSystem::customerRegistration() {
    UIUtils::clearScreen();
    UIUtils::printHeader("CUSTOMER REGISTRATION");

    string name = UIUtils::getStringInput("Enter Full Name: ");
    string phone = UIUtils::getStringInput("Enter Phone Number (10 digits): ");
    string email = UIUtils::getStringInput("Enter Email Address: ");

    if (findCustomerByEmail(email) != nullptr) {
        UIUtils::printError("Email is already registered! Please login or use a different email.");
        UIUtils::pressEnterToContinue();
        return;
    }

    string password = UIUtils::getStringInput("Create Password: ");
    string license = UIUtils::getStringInput("Enter Driving License Number: ");

    string newId = generateCustomerId();
    customers.emplace_back(newId, name, phone, email, password, license);
    saveAllData();

    UIUtils::loadingAnimation("Creating account", 600);
    UIUtils::printSuccess("Registration successful! Your Customer ID is: " + newId);
    UIUtils::pressEnterToContinue();
}

void RentalSystem::customerLogin() {
    UIUtils::clearScreen();
    UIUtils::printHeader("CUSTOMER LOGIN");

    string email = UIUtils::getStringInput("Enter Email: ");
    string password = UIUtils::getStringInput("Enter Password: ");

    Customer* cust = findCustomerByEmail(email);
    if (cust && cust->validatePassword(password)) {
        UIUtils::loadingAnimation("Logging in", 500);
        UIUtils::printSuccess("Welcome back, " + cust->getName() + "!");
        customerDashboard(*cust);
    } else {
        UIUtils::printError("Invalid email or password! Please try again.");
        UIUtils::pressEnterToContinue();
    }
}

void RentalSystem::customerDashboard(Customer& customer) {
    bool inDashboard = true;
    while (inDashboard) {
        UIUtils::clearScreen();
        UIUtils::printHeader("CUSTOMER DASHBOARD");
        cout << "  Logged in as: " << customer.getName() << " (" << customer.getId() << ")\n";
        UIUtils::printSeparator('-', 55);
        cout << "  1. View All Available Vehicles\n";
        cout << "  2. Search Vehicle\n";
        cout << "  3. Rent a Vehicle\n";
        cout << "  4. Return a Vehicle\n";
        cout << "  5. View My Rental History\n";
        cout << "  6. View My Profile\n";
        cout << "  7. Logout\n";
        UIUtils::printSeparator('-', 55);

        int choice = UIUtils::getMenuChoice(1, 7);
        switch (choice) {
            case 1:
                viewAvailableVehicles();
                UIUtils::pressEnterToContinue();
                break;
            case 2:
                searchVehicle();
                break;
            case 3:
                rentVehicle(customer);
                break;
            case 4:
                returnVehicle(customer);
                break;
            case 5:
                viewRentalHistory(customer);
                break;
            case 6:
                viewProfile(customer);
                break;
            case 7:
                UIUtils::printInfo("Logged out successfully.");
                inDashboard = false;
                break;
        }
    }
}

void RentalSystem::searchVehicle() {
    UIUtils::clearScreen();
    UIUtils::printHeader("SEARCH VEHICLES");
    cout << "Search Criteria:\n";
    cout << "  1. Search by Type (Car / Bike)\n";
    cout << "  2. Search by Brand\n";
    cout << "  3. Search by Max Price Per Day\n";
    cout << "  4. Back to Dashboard\n";

    int choice = UIUtils::getMenuChoice(1, 4);
    vector<shared_ptr<Vehicle>> results;

    if (choice == 1) {
        cout << "Select Type: 1. Car | 2. Bike\n";
        int t = UIUtils::getMenuChoice(1, 2);
        string typeStr = (t == 1 ? "Car" : "Bike");
        for (const auto& v : vehicles) {
            if (v && v->getType() == typeStr) results.push_back(v);
        }
    } else if (choice == 2) {
        string brand = UIUtils::getStringInput("Enter Brand name (or part of brand): ");
        string brandLower = brand;
        transform(brandLower.begin(), brandLower.end(), brandLower.begin(), ::tolower);
        for (const auto& v : vehicles) {
            if (v) {
                string vBrandLower = v->getBrand();
                transform(vBrandLower.begin(), vBrandLower.end(), vBrandLower.begin(), ::tolower);
                if (vBrandLower.find(brandLower) != string::npos) {
                    results.push_back(v);
                }
            }
        }
    } else if (choice == 3) {
        double maxPrice = UIUtils::getDoubleInput("Enter Maximum Price Per Day (Rs.): ", 1.0);
        for (const auto& v : vehicles) {
            if (v && v->getPricePerDay() <= maxPrice) results.push_back(v);
        }
    } else {
        return;
    }

    UIUtils::clearScreen();
    UIUtils::printHeader("SEARCH RESULTS");
    UIUtils::printVehicleTable(results);
    UIUtils::pressEnterToContinue();
}

void RentalSystem::rentVehicle(Customer& customer) {
    UIUtils::clearScreen();
    UIUtils::printHeader("RENT A VEHICLE");

    // Display available vehicles
    vector<shared_ptr<Vehicle>> avail;
    for (const auto& v : vehicles) {
        if (v && v->isAvailable()) avail.push_back(v);
    }

    if (avail.empty()) {
        UIUtils::printWarning("Sorry! No vehicles are currently available for rent.");
        UIUtils::pressEnterToContinue();
        return;
    }

    UIUtils::printVehicleTable(avail);

    string vid = UIUtils::getStringInput("Enter Vehicle ID to Rent: ");
    auto v = findVehicleById(vid);

    if (!v) {
        UIUtils::printError("Vehicle ID '" + vid + "' does not exist!");
        UIUtils::pressEnterToContinue();
        return;
    }

    if (!v->isAvailable()) {
        UIUtils::printError("Vehicle '" + vid + "' is already rented! Please choose another.");
        UIUtils::pressEnterToContinue();
        return;
    }

    int days = UIUtils::getIntInput("Enter Rental Days (1-90): ", 1, 90);
    double totalAmount = v->calculateRent(days);

    // Dynamic quote breakdown
    cout << "\n==================================================" << endl;
    cout << "               BOOKING QUOTATION" << endl;
    cout << "==================================================" << endl;
    cout << "  Customer       : " << customer.getName() << " (" << customer.getId() << ")" << endl;
    cout << "  Vehicle        : " << v->getBrand() << " " << v->getModel() << endl;
    cout << "  Type           : " << v->getType() << endl;
    cout << "  Price Per Day  : Rs. " << fixed << setprecision(0) << v->getPricePerDay() << endl;
    cout << "  Rental Days    : " << days << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "  Total Amount   : Rs. " << fixed << setprecision(2) << totalAmount << endl;
    cout << "==================================================" << endl;

    if (!UIUtils::getConfirmation("Confirm Booking?")) {
        UIUtils::printInfo("Booking cancelled by customer.");
        UIUtils::pressEnterToContinue();
        return;
    }

    string rentalId = generateRentalId();
    if (!processPayment(rentalId, customer.getId(), totalAmount)) {
        UIUtils::printError("Payment failed! Booking could not be completed.");
        UIUtils::pressEnterToContinue();
        return;
    }

    // Update vehicle state
    v->setAvailable(false);

    string startDate = getCurrentDate();
    string endDate = calculateEndDate(days);

    Rental newRental(rentalId, customer.getId(), v->getId(), days, totalAmount, startDate, endDate);
    rentals.push_back(newRental);
    saveAllData();

    // Display receipt
    UIUtils::clearScreen();
    cout << "=======================================================" << endl;
    cout << "                 OFFICIAL BOOKING RECEIPT              " << endl;
    cout << "=======================================================" << endl;
    cout << "  Rental ID        : " << rentalId << endl;
    cout << "  Customer ID      : " << customer.getId() << endl;
    cout << "  Customer Name    : " << customer.getName() << endl;
    cout << "  Phone Number     : " << customer.getPhone() << endl;
    cout << "  Vehicle ID       : " << v->getId() << endl;
    cout << "  Vehicle Details  : " << v->getBrand() << " " << v->getModel() << " (" << v->getType() << ")" << endl;
    cout << "  Rental Period    : " << startDate << " to " << endDate << " (" << days << " days)" << endl;
    cout << "  Rate Per Day     : Rs. " << fixed << setprecision(0) << v->getPricePerDay() << endl;
    cout << "  Total Paid       : Rs. " << fixed << setprecision(2) << totalAmount << endl;
    cout << "  Booking Status   : CONFIRMED & ACTIVE" << endl;
    cout << "=======================================================" << endl;
    UIUtils::printSuccess("Vehicle booked successfully! Please collect the keys at the counter.");
    UIUtils::pressEnterToContinue();
}

bool RentalSystem::processPayment(const string& rentalId, const string& customerId, double amount) {
    cout << "\n--------------------------------------------------" << endl;
    cout << "               PAYMENT CHECKOUT" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "  Amount Due: Rs. " << fixed << setprecision(2) << amount << endl;
    cout << "  Select Payment Mode:\n";
    cout << "    1. Cash\n";
    cout << "    2. UPI\n";
    cout << "    3. Cancel Payment\n";
    int choice = UIUtils::getMenuChoice(1, 3);

    if (choice == 3) return false;

    string method = (choice == 1) ? "Cash" : "UPI";
    string txnId = generateTransactionId();
    string paymentDate = getCurrentDate();

    if (method == "UPI") {
        cout << "\n  UPI Payment Gateway Simulation:" << endl;
        cout << "  Enter UPI ID (e.g., yourname@upi): ";
        string upi = UIUtils::getStringInput("");
        UIUtils::loadingAnimation("  Contacting Bank & Processing UPI Payment", 800);
    } else {
        UIUtils::loadingAnimation("  Processing Cash Payment Receipt", 600);
    }

    Payment payment(txnId, rentalId, customerId, amount, method, paymentDate);
    payments.push_back(payment);
    saveAllData();

    payment.generateReceipt();
    return true;
}

void RentalSystem::returnVehicle(Customer& customer) {
    UIUtils::clearScreen();
    UIUtils::printHeader("RETURN A RENTED VEHICLE");

    // Filter active rentals for this customer
    vector<Rental> activeRentals;
    for (const auto& r : rentals) {
        if (r.getCustomerId() == customer.getId() && !r.isReturned()) {
            activeRentals.push_back(r);
        }
    }

    if (activeRentals.empty()) {
        UIUtils::printInfo("You have no active rentals to return.");
        UIUtils::pressEnterToContinue();
        return;
    }

    UIUtils::printRentalTable(activeRentals);

    string rid = UIUtils::getStringInput("Enter Rental ID to return: ");
    Rental* rental = findRentalById(rid);

    if (!rental || rental->getCustomerId() != customer.getId()) {
        UIUtils::printError("Rental ID not found in your active bookings!");
        UIUtils::pressEnterToContinue();
        return;
    }

    if (rental->isReturned()) {
        UIUtils::printWarning("This rental has already been returned!");
        UIUtils::pressEnterToContinue();
        return;
    }

    auto v = findVehicleById(rental->getVehicleId());
    if (!v) {
        UIUtils::printError("Associated vehicle record not found!");
        UIUtils::pressEnterToContinue();
        return;
    }

    cout << "\nRental Found:\n";
    cout << "  Rental ID      : " << rental->getRentalId() << "\n";
    cout << "  Vehicle        : " << v->getBrand() << " " << v->getModel() << "\n";
    cout << "  Expected End   : " << rental->getEndDate() << "\n";

    // Extra days simulation check
    cout << "\nWere there any extra days past the agreed return date?\n";
    int extraDays = UIUtils::getIntInput("Enter extra days (0 if returned on time): ", 0, 30);

    double extraCharge = 0.0;
    if (extraDays > 0) {
        // Compile-time polymorphism: calculateCharges with extra days and pricePerDay (1.5x late rate)
        double totalWithExtra = rental->calculateCharges(extraDays, v->getPricePerDay());
        extraCharge = totalWithExtra - rental->getTotalAmount();

        cout << "\n==================================================" << endl;
        cout << "            LATE RETURN CHARGES DETECTED           " << endl;
        cout << "==================================================" << endl;
        cout << "  Extra Days       : " << extraDays << endl;
        cout << "  Late Fee Rate    : 1.5x Daily Rate (Rs. " << (v->getPricePerDay() * 1.5) << "/day)" << endl;
        cout << "  Additional Dues  : Rs. " << fixed << setprecision(2) << extraCharge << endl;
        cout << "==================================================" << endl;

        if (!processPayment(rental->getRentalId() + "-LATE", customer.getId(), extraCharge)) {
            UIUtils::printError("Late fee payment incomplete. Return cannot be finalized.");
            UIUtils::pressEnterToContinue();
            return;
        }
    }

    string returnDate = getCurrentDate();
    rental->markReturned(returnDate);
    v->setAvailable(true);
    saveAllData();

    // Return receipt
    UIUtils::clearScreen();
    cout << "=======================================================" << endl;
    cout << "              VEHICLE RETURN CONFIRMATION              " << endl;
    cout << "=======================================================" << endl;
    cout << "  Rental ID        : " << rental->getRentalId() << endl;
    cout << "  Customer         : " << customer.getName() << " (" << customer.getId() << ")" << endl;
    cout << "  Vehicle Returned : " << v->getBrand() << " " << v->getModel() << " (" << v->getId() << ")" << endl;
    cout << "  Return Date      : " << returnDate << endl;
    cout << "  Original Rental  : " << rental->getDays() << " days (Rs. " << rental->getTotalAmount() << ")" << endl;
    if (extraDays > 0) {
        cout << "  Extra Days       : " << extraDays << " days" << endl;
        cout << "  Late Charges     : Rs. " << fixed << setprecision(2) << extraCharge << endl;
    }
    cout << "  Vehicle Status   : AVAILABLE FOR RENT" << endl;
    cout << "  Account Status   : SETTLED IN FULL" << endl;
    cout << "=======================================================" << endl;
    UIUtils::printSuccess("Vehicle return processed successfully! Thank you.");
    UIUtils::pressEnterToContinue();
}

void RentalSystem::viewRentalHistory(const Customer& customer) {
    UIUtils::clearScreen();
    UIUtils::printHeader("MY RENTAL HISTORY");

    vector<Rental> userRentals;
    for (const auto& r : rentals) {
        if (r.getCustomerId() == customer.getId()) {
            userRentals.push_back(r);
        }
    }

    UIUtils::printRentalTable(userRentals);
    UIUtils::pressEnterToContinue();
}

void RentalSystem::viewProfile(const Customer& customer) {
    UIUtils::clearScreen();
    UIUtils::printHeader("CUSTOMER PROFILE");
    customer.display();
    UIUtils::pressEnterToContinue();
}

