#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <memory>

class Vehicle;
class Customer;
class Rental;
class Payment;

class FileHandler {
    static const std::string DATA_DIR;
    static const std::string VEHICLE_FILE;
    static const std::string CUSTOMER_FILE;
    static const std::string RENTAL_FILE;
    static const std::string PAYMENT_FILE;

public:
    // Save all records (overwrite file)
    static void saveVehicles(const std::vector<std::shared_ptr<Vehicle>>& vehicles);
    static void saveCustomers(const std::vector<Customer>& customers);
    static void saveRentals(const std::vector<Rental>& rentals);
    static void savePayments(const std::vector<Payment>& payments);

    // Load all records
    static std::vector<std::shared_ptr<Vehicle>> loadVehicles();
    static std::vector<Customer> loadCustomers();
    static std::vector<Rental> loadRentals();
    static std::vector<Payment> loadPayments();

    // COMPILE-TIME POLYMORPHISM - function overloading
    static void appendRecord(const std::string& filename, const std::string& record);
    static void appendRecord(const std::string& filename, const std::vector<std::string>& records);
    
    static bool fileExists(const std::string& filename);
    static void ensureDataDirectory();
};

#endif
