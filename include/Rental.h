#ifndef RENTAL_H
#define RENTAL_H

#include <string>
#include <iostream>

class Rental {
    std::string rentalId;
    std::string customerId;
    std::string vehicleId;
    int days;
    double totalAmount;
    std::string startDate;
    std::string endDate;
    bool returned;
    std::string returnDate;

public:
    Rental();
    Rental(const std::string& rentalId, const std::string& customerId, const std::string& vehicleId,
           int days, double totalAmount, const std::string& startDate, const std::string& endDate);

    // Getters
    std::string getRentalId() const;
    std::string getCustomerId() const;
    std::string getVehicleId() const;
    int getDays() const;
    double getTotalAmount() const;
    std::string getStartDate() const;
    std::string getEndDate() const;
    bool isReturned() const;
    std::string getReturnDate() const;

    void markReturned(const std::string& returnDate);

    // COMPILE-TIME POLYMORPHISM - function overloading
    double calculateCharges() const;
    double calculateCharges(int extraDays, double pricePerDay) const;

    std::string serialize() const;
    void display() const;

    // OPERATOR OVERLOADING
    bool operator==(const Rental& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Rental& r);
};

#endif

