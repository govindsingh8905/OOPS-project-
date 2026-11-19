#include "Car.h"

using namespace std;

// Constructor
Car::Car(const string& id, const string& brand, const string& model,
         double pricePerDay, int seats, const string& fuelType, bool hasAC)
    : Vehicle(id, brand, model, pricePerDay), seats(seats), fuelType(fuelType), hasAC(hasAC) {}

// Destructor
Car::~Car() = default;

// Override virtual functions
string Car::getType() const {
    return "Car";
}

double Car::calculateRent(int days) const {
    return pricePerDay * days;
}

double Car::calculateRent(int days, bool withInsurance) const {
    double base = pricePerDay * days;
    if (withInsurance) {
        base += 500.0 * days;
    }
    return base;
}

void Car::displayDetails() const {
    cout << "========== CAR DETAILS ==========" << endl;
    cout << "  ID           : " << id << endl;
    cout << "  Brand        : " << brand << endl;
    cout << "  Model        : " << model << endl;
    cout << "  Price/Day    : Rs. " << pricePerDay << endl;
    cout << "  Status       : " << (available ? "Available" : "Rented") << endl;
    cout << "  Seats        : " << seats << endl;
    cout << "  Fuel Type    : " << fuelType << endl;
    cout << "  AC           : " << (hasAC ? "Yes" : "No") << endl;
    cout << "=================================" << endl;
}

string Car::serialize() const {
    ostringstream oss;
    oss << id << "|" << brand << "|" << model << "|" << pricePerDay << "|"
        << (available ? 1 : 0) << "|Car|" << seats << "|" << fuelType << "|"
        << (hasAC ? 1 : 0);
    return oss.str();
}

unique_ptr<Vehicle> Car::clone() const {
    return make_unique<Car>(*this);
}

// Getters
int Car::getSeats() const { return seats; }
string Car::getFuelType() const { return fuelType; }
bool Car::getHasAC() const { return hasAC; }
