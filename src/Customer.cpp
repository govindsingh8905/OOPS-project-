#include "Customer.h"
#include <iomanip>
#include <sstream>

using namespace std;

Customer::Customer() : id(""), name(""), phone(""), email(""), password(""), licenseNumber("") {}

Customer::Customer(const string& id, const string& name, const string& phone,
                   const string& email, const string& password, const string& licenseNumber)
    : id(id), name(name), phone(phone), email(email), password(password), licenseNumber(licenseNumber) {}

// Getters
string Customer::getId() const { return id; }
string Customer::getName() const { return name; }
string Customer::getPhone() const { return phone; }
string Customer::getEmail() const { return email; }
string Customer::getLicenseNumber() const { return licenseNumber; }

// Setters
void Customer::setName(const string& name) { this->name = name; }
void Customer::setPhone(const string& phone) { this->phone = phone; }
void Customer::setEmail(const string& email) { this->email = email; }

bool Customer::validatePassword(const string& pwd) const {
    return password == pwd;
}

string Customer::serialize() const {
    return id + "|" + name + "|" + phone + "|" + email + "|" + password + "|" + licenseNumber;
}

void Customer::display() const {
    cout << "---------- Customer Details ----------" << endl;
    cout << "  ID             : " << id << endl;
    cout << "  Name           : " << name << endl;
    cout << "  Phone          : " << phone << endl;
    cout << "  Email          : " << email << endl;
    cout << "  License Number : " << licenseNumber << endl;
    cout << "--------------------------------------" << endl;
}

// OPERATOR OVERLOADING
bool Customer::operator==(const Customer& other) const {
    return id == other.id;
}

ostream& operator<<(ostream& os, const Customer& c) {
    os << c.name << " | " << c.email << " | " << c.phone;
    return os;
}

