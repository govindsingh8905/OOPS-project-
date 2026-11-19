#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <memory>
#include <sstream>

class Vehicle {
protected:
    std::string id;
    std::string brand;
    std::string model;
    double pricePerDay;
    bool available;

public:
    Vehicle(const std::string& id, const std::string& brand, const std::string& model, double pricePerDay);
    virtual ~Vehicle();

    // Pure virtual functions - ABSTRACTION
    virtual std::string getType() const = 0;
    virtual double calculateRent(int days) const = 0;
    virtual void displayDetails() const = 0;
    virtual std::string serialize() const = 0;
    virtual std::unique_ptr<Vehicle> clone() const = 0;

    // Getters - ENCAPSULATION
    std::string getId() const;
    std::string getBrand() const;
    std::string getModel() const;
    double getPricePerDay() const;
    bool isAvailable() const;

    // Setters
    void setAvailable(bool status);
    void setBrand(const std::string& brand);
    void setModel(const std::string& model);
    void setPricePerDay(double price);

    // OPERATOR OVERLOADING
    bool operator==(const Vehicle& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v);
};

#endif
