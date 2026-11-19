#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>

class Customer {
    std::string id;
    std::string name;
    std::string phone;
    std::string email;
    std::string password;
    std::string licenseNumber;

public:
    Customer();
    Customer(const std::string& id, const std::string& name, const std::string& phone,
             const std::string& email, const std::string& password, const std::string& licenseNumber);

    // Getters
    std::string getId() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getLicenseNumber() const;

    // Setters
    void setName(const std::string& name);
    void setPhone(const std::string& phone);
    void setEmail(const std::string& email);

    bool validatePassword(const std::string& pwd) const;
    std::string serialize() const;
    void display() const;

    // OPERATOR OVERLOADING
    bool operator==(const Customer& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Customer& c);
};

#endif

