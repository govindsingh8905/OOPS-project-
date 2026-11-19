#include "Payment.h"
#include <iomanip>
#include <sstream>

using namespace std;

Payment::Payment()
    : transactionId(""), rentalId(""), customerId(""), amount(0.0),
      paymentMethod(""), paymentDate("") {}

Payment::Payment(const string& transactionId, const string& rentalId, const string& customerId,
                 double amount, const string& paymentMethod, const string& paymentDate)
    : transactionId(transactionId), rentalId(rentalId), customerId(customerId),
      amount(amount), paymentMethod(paymentMethod), paymentDate(paymentDate) {}

// Getters
string Payment::getTransactionId() const { return transactionId; }
string Payment::getRentalId() const { return rentalId; }
string Payment::getCustomerId() const { return customerId; }
double Payment::getAmount() const { return amount; }
string Payment::getPaymentMethod() const { return paymentMethod; }
string Payment::getPaymentDate() const { return paymentDate; }

string Payment::serialize() const {
    ostringstream oss;
    oss << transactionId << "|" << rentalId << "|" << customerId << "|"
        << fixed << setprecision(2) << amount << "|" << paymentMethod << "|" << paymentDate;
    return oss.str();
}

void Payment::display() const {
    cout << "Payment [" << transactionId << "] Rental: " << rentalId
         << " | Amount: Rs. " << fixed << setprecision(2) << amount
         << " | Method: " << paymentMethod << " | Date: " << paymentDate << endl;
}

void Payment::generateReceipt() const {
    cout << "==================================================" << endl;
    cout << "              PAYMENT RECEIPT" << endl;
    cout << "==================================================" << endl;
    cout << "  Transaction ID : " << transactionId << endl;
    cout << "  Rental ID      : " << rentalId << endl;
    cout << "  Customer ID    : " << customerId << endl;
    cout << "  Amount         : Rs. " << fixed << setprecision(2) << amount << endl;
    cout << "  Payment Method : " << paymentMethod << endl;
    cout << "  Date           : " << paymentDate << endl;
    cout << "==================================================" << endl;
}

// OPERATOR OVERLOADING
ostream& operator<<(ostream& os, const Payment& p) {
    os << "Payment [" << p.transactionId << "] Rental: " << p.rentalId
       << " | Amount: Rs. " << fixed << setprecision(2) << p.amount
       << " | Method: " << p.paymentMethod << " | Date: " << p.paymentDate;
    return os;
}

