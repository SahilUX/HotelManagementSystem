#include "../include/Customer.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

Customer::Customer(const string& name, const string& fromDate, int roomNumber)
    : name(name), fromDate(fromDate), roomNumber(roomNumber) {}

void Customer::display() const {
    cout << "Customer Name: " << name << endl;
    cout << "Check-in Date: " << fromDate << endl;
    if (!toDate.empty()) {
        cout << "Check-out Date: " << toDate << endl;
    }
    cout << "Room Number: " << roomNumber << endl;
}

string Customer::getName() const {
    return name;
}

int Customer::getRoomNumber() const {
    return roomNumber;
}

string Customer::getCheckInDate() const {
    return fromDate;
}

string Customer::getCheckOutDate() const {
    return toDate;
}

void Customer::setCheckOutDate(const string& toDate) {
    this->toDate = toDate;
}

time_t Customer::parseDate(const string& date) const {
    struct tm tm = {};
    istringstream ss(date);
    ss >> get_time(&tm, "%Y-%m-%d");
    return mktime(&tm);
}

int Customer::calculateDaysStayed() const {
    time_t checkInTime = parseDate(fromDate);
    time_t checkOutTime = parseDate(toDate);
    return difftime(checkOutTime, checkInTime) / (60 * 60 * 24) + 1;
}
