#include "Vehicle.h"

using namespace std;

// Constructor
Vehicle::Vehicle(const string& id, const string& brand, const string& model, double pricePerDay)
    : id(id), brand(brand), model(model), pricePerDay(pricePerDay), available(true) {}

// Destructor
Vehicle::~Vehicle() = default;

// Getters
string Vehicle::getId() const { return id; }
string Vehicle::getBrand() const { return brand; }
string Vehicle::getModel() const { return model; }
double Vehicle::getPricePerDay() const { return pricePerDay; }
bool Vehicle::isAvailable() const { return available; }

// Setters
void Vehicle::setAvailable(bool status) { available = status; }
void Vehicle::setBrand(const string& brand) { this->brand = brand; }
void Vehicle::setModel(const string& model) { this->model = model; }
void Vehicle::setPricePerDay(double price) { pricePerDay = price; }

// Operator overloading
bool Vehicle::operator==(const Vehicle& other) const {
    return id == other.id;
}

ostream& operator<<(ostream& os, const Vehicle& v) {
    os << "[" << v.id << "] " << v.brand << " " << v.model
       << " (" << v.getType() << ") - Rs. " << v.pricePerDay << "/day - "
       << (v.available ? "Available" : "Rented");
    return os;
}
