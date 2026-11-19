#include "Bike.h"

using namespace std;

// Constructor
Bike::Bike(const string& id, const string& brand, const string& model,
           double pricePerDay, int engineCC, const string& bikeType)
    : Vehicle(id, brand, model, pricePerDay), engineCC(engineCC), bikeType(bikeType) {}

// Destructor
Bike::~Bike() = default;

// Override virtual functions
string Bike::getType() const {
    return "Bike";
}

double Bike::calculateRent(int days) const {
    return pricePerDay * days;
}

double Bike::calculateRent(int days, bool withHelmet) const {
    double base = pricePerDay * days;
    if (withHelmet) {
        base += 100.0 * days;
    }
    return base;
}

void Bike::displayDetails() const {
    cout << "========== BIKE DETAILS ==========" << endl;
    cout << "  ID           : " << id << endl;
    cout << "  Brand        : " << brand << endl;
    cout << "  Model        : " << model << endl;
    cout << "  Price/Day    : Rs. " << pricePerDay << endl;
    cout << "  Status       : " << (available ? "Available" : "Rented") << endl;
    cout << "  Engine CC    : " << engineCC << endl;
    cout << "  Bike Type    : " << bikeType << endl;
    cout << "==================================" << endl;
}

string Bike::serialize() const {
    ostringstream oss;
    oss << id << "|" << brand << "|" << model << "|" << pricePerDay << "|"
        << (available ? 1 : 0) << "|Bike|" << engineCC << "|" << bikeType;
    return oss.str();
}

unique_ptr<Vehicle> Bike::clone() const {
    return make_unique<Bike>(*this);
}

// Getters
int Bike::getEngineCC() const { return engineCC; }
string Bike::getBikeType() const { return bikeType; }
