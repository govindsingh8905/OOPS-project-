#include "Rental.h"
#include <iomanip>
#include <sstream>

using namespace std;

Rental::Rental()
    : rentalId(""), customerId(""), vehicleId(""), days(0), totalAmount(0.0),
      startDate(""), endDate(""), returned(false), returnDate("N/A") {}

Rental::Rental(const string& rentalId, const string& customerId, const string& vehicleId,
               int days, double totalAmount, const string& startDate, const string& endDate)
    : rentalId(rentalId), customerId(customerId), vehicleId(vehicleId),
      days(days), totalAmount(totalAmount), startDate(startDate), endDate(endDate),
      returned(false), returnDate("N/A") {}

// Getters
string Rental::getRentalId() const { return rentalId; }
string Rental::getCustomerId() const { return customerId; }
string Rental::getVehicleId() const { return vehicleId; }
int Rental::getDays() const { return days; }
double Rental::getTotalAmount() const { return totalAmount; }
string Rental::getStartDate() const { return startDate; }
string Rental::getEndDate() const { return endDate; }
bool Rental::isReturned() const { return returned; }
string Rental::getReturnDate() const { return returnDate; }

void Rental::markReturned(const string& returnDate) {
    this->returned = true;
    this->returnDate = returnDate;
}

// COMPILE-TIME POLYMORPHISM - function overloading
double Rental::calculateCharges() const {
    return totalAmount;
}

double Rental::calculateCharges(int extraDays, double pricePerDay) const {
    return totalAmount + (extraDays * pricePerDay * 1.5);
}

string Rental::serialize() const {
    ostringstream oss;
    oss << rentalId << "|" << customerId << "|" << vehicleId << "|"
        << days << "|" << fixed << setprecision(2) << totalAmount << "|"
        << startDate << "|" << endDate << "|" << (returned ? "1" : "0") << "|" << returnDate;
    return oss.str();
}

void Rental::display() const {
    cout << "---------- Rental Details ----------" << endl;
    cout << "  Rental ID   : " << rentalId << endl;
    cout << "  Customer ID : " << customerId << endl;
    cout << "  Vehicle ID  : " << vehicleId << endl;
    cout << "  Days        : " << days << endl;
    cout << "  Total Amount: Rs. " << fixed << setprecision(2) << totalAmount << endl;
    cout << "  Start Date  : " << startDate << endl;
    cout << "  End Date    : " << endDate << endl;
    cout << "  Returned    : " << (returned ? "Yes" : "No") << endl;
    cout << "  Return Date : " << returnDate << endl;
    cout << "------------------------------------" << endl;
}

// OPERATOR OVERLOADING
bool Rental::operator==(const Rental& other) const {
    return rentalId == other.rentalId;
}

ostream& operator<<(ostream& os, const Rental& r) {
    os << "Rental [" << r.rentalId << "] Customer: " << r.customerId
       << " | Vehicle: " << r.vehicleId << " | Days: " << r.days
       << " | Amount: Rs. " << fixed << setprecision(2) << r.totalAmount
       << " | " << (r.returned ? "Returned" : "Active");
    return os;
}

