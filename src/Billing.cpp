#include "../include/Billing.h"
#include <iostream>

void Billing::addBill(const Customer& customer, double amount, const string& details) {
    bills.push_back({customer, amount, details});
}

void Billing::display() const {
    for (const auto& bill : bills) {
        cout << "Customer: " << bill.customer.getName() << ", Amount: " << bill.amount << " AED, Details: " << bill.details << endl;
    }
}

const vector<Billing::Bill>& Billing::getBills() const {
    return bills;
}

void Billing::clear() {
    bills.clear();
}
