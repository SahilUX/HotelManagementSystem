#include "../include/Billing.h"
#include <iostream>

// Add a new bill to the billing system
void Billing::addBill(const Customer& customer, int roomNumber, double amount, const string& details) {
    bills.push_back({customer, roomNumber, amount, details});
}

// Display all bills in the billing system
void Billing::display() const {
    for (const auto& bill : bills) {
        cout << "Customer: " << bill.customer.getName()
             << ", Room Number: " << bill.roomNumber
             << ", Amount: " << bill.amount
             << " AED, Details: " << bill.details << endl;
    }
}

// Get all bills in the billing system
const vector<Billing::Bill>& Billing::getBills() const {
    return bills;
}


void Billing::clear() {
    bills.clear();
}
