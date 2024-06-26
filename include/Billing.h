#ifndef BILLING_H
#define BILLING_H

#include <vector>
#include "Customer.h"

using namespace std;

class Billing {
public:
    struct Bill {
        Customer customer;
        int roomNumber;
        double amount;
        string details;
    };

    void addBill(const Customer& customer, int roomNumber, double amount, const string& details);
    void display() const;
    const vector<Bill>& getBills() const;
    void clear();

private:
    vector<Bill> bills;
};

#endif
