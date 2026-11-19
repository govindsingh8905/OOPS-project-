#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
    int seats;
    std::string fuelType;  // Petrol, Diesel, Electric, CNG
    bool hasAC;

public:
    Car(const std::string& id, const std::string& brand, const std::string& model,
        double pricePerDay, int seats, const std::string& fuelType, bool hasAC);
    ~Car() override;

    // Override virtual functions
    std::string getType() const override;
    double calculateRent(int days) const override;
    void displayDetails() const override;
    std::string serialize() const override;
    std::unique_ptr<Vehicle> clone() const override;

    // COMPILE-TIME POLYMORPHISM - function overloading
    double calculateRent(int days, bool withInsurance) const;

    // Getters
    int getSeats() const;
    std::string getFuelType() const;
    bool getHasAC() const;
};

#endif
