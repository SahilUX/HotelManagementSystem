#include "../include/Customer.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor for Customer class
Customer::Customer(const string& name, const string& fromDate, int roomNumber)
    : name(name), fromDate(fromDate), roomNumber(roomNumber) {}

// Display customer details
void Customer::display() const {
    cout << "Customer Name: " << name << endl;
    cout << "Check-in Date: " << fromDate << endl;
    if (!toDate.empty()) {
        cout << "Check-out Date: " << toDate << endl;
    }
    cout << "Room Number: " << roomNumber << endl;
}

// Get customer name
string Customer::getName() const {
    return name;
}

// Get room number
int Customer::getRoomNumber() const {
    return roomNumber;
}

// Get check-in date
string Customer::getCheckInDate() const {
    return fromDate;
}

// Get check-out date
string Customer::getCheckOutDate() const {
    return toDate;
}

// Set check-out date
void Customer::setCheckOutDate(const string& toDate) {
    this->toDate = toDate;
}

// Calculate number of days stayed
time_t Customer::parseDate(const string& date) const {
    struct tm tm = {};
    istringstream ss(date);
    ss >> get_time(&tm, "%Y-%m-%d");
    return mktime(&tm);
}

// Calculate number of days stayed
int Customer::calculateDaysStayed() const {
    time_t checkInTime = parseDate(fromDate);
    time_t checkOutTime = parseDate(toDate);
    return difftime(checkOutTime, checkInTime) / (60 * 60 * 24) + 1;
}
