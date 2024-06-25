#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

class Customer {
public:
    Customer(const string& name, const string& fromDate, int roomNumber);
    void display() const;
    string getName() const;
    int getRoomNumber() const;
    string getCheckInDate() const;
    string getCheckOutDate() const;
    void setCheckOutDate(const string& toDate);
    int calculateDaysStayed() const;

private:
    string name;
    string fromDate;
    string toDate;
    int roomNumber;
    time_t parseDate(const string& date) const;
};

#endif
