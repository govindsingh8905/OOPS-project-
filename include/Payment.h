#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <iostream>

class Payment {
    std::string transactionId;
    std::string rentalId;
    std::string customerId;
    double amount;
    std::string paymentMethod;
    std::string paymentDate;

public:
    Payment();
    Payment(const std::string& transactionId, const std::string& rentalId, const std::string& customerId,
            double amount, const std::string& paymentMethod, const std::string& paymentDate);

    // Getters
    std::string getTransactionId() const;
    std::string getRentalId() const;
    std::string getCustomerId() const;
    double getAmount() const;
    std::string getPaymentMethod() const;
    std::string getPaymentDate() const;

    std::string serialize() const;
    void display() const;
    void generateReceipt() const;

    // OPERATOR OVERLOADING
    friend std::ostream& operator<<(std::ostream& os, const Payment& p);
};

#endif

