#ifndef BIKE_H
#define BIKE_H

#include "Vehicle.h"

class Bike : public Vehicle {
    int engineCC;
    std::string bikeType;  // Sport, Cruiser, Standard, Scooter

public:
    Bike(const std::string& id, const std::string& brand, const std::string& model,
         double pricePerDay, int engineCC, const std::string& bikeType);
    ~Bike() override;

    std::string getType() const override;
    double calculateRent(int days) const override;
    void displayDetails() const override;
    std::string serialize() const override;
    std::unique_ptr<Vehicle> clone() const override;

    // COMPILE-TIME POLYMORPHISM
    double calculateRent(int days, bool withHelmet) const;

    int getEngineCC() const;
    std::string getBikeType() const;
};

#endif
