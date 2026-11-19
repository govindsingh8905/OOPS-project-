#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include <vector>
#include <memory>
#include <string>
#include <map>

#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"
#include "Customer.h"
#include "Admin.h"
#include "Rental.h"
#include "Payment.h"
#include "UIUtils.h"
#include "FileHandler.h"

class RentalSystem {
private:
    std::vector<std::shared_ptr<Vehicle>> vehicles;
    std::vector<Customer> customers;
    std::vector<Rental> rentals;
    std::vector<Payment> payments;
    Admin admin;

    // ID Generators
    std::string generateVehicleId();
    std::string generateCustomerId();
    std::string generateRentalId();
    std::string generateTransactionId();

    // Helper functions
    std::string getCurrentDate();
    std::string calculateEndDate(int daysFromNow);
    std::shared_ptr<Vehicle> findVehicleById(const std::string& id);
    Customer* findCustomerById(const std::string& id);
    Customer* findCustomerByEmail(const std::string& email);
    Rental* findRentalById(const std::string& id);

    void seedDefaultDataIfEmpty();

public:
    RentalSystem();
    ~RentalSystem();

    void run();

    // Welcome Menu Actions
    void adminLogin();
    void customerRegistration();
    void customerLogin();

    // Admin Dashboard & Actions
    void adminDashboard();
    void addVehicle();
    void removeVehicle();
    void updateVehicle();
    void viewAllVehicles();
    void viewAvailableVehicles();
    void viewRentedVehicles();
    void viewAllCustomers();
    void viewAllRentals();
    void viewRevenueReport();

    // Customer Dashboard & Actions
    void customerDashboard(Customer& customer);
    void searchVehicle();
    void rentVehicle(Customer& customer);
    void returnVehicle(Customer& customer);
    void viewRentalHistory(const Customer& customer);
    void viewProfile(const Customer& customer);

    // Payment Processing
    bool processPayment(const std::string& rentalId, const std::string& customerId, double amount);

    // Persistence
    void saveAllData();
    void loadAllData();
};

#endif

