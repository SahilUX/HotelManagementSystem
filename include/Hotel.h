#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include <string>
#include "Room.h"
#include "Customer.h"
#include "Billing.h"

using namespace std;

class Hotel {
public:
    Hotel(const string& name);
    void initialize(const string& filename);
    void displayDescription() const;
    void checkIn(const string& customerName, const string& fromDate, int roomNumber);
    void checkOut(int roomNumber);
    void viewAvailableRooms() const;
    void viewBookedRooms() const;
    void viewRoomsByType(const string& type) const;
    void viewBilling() const;
    void saveState(const string& filename) const;

private:
    string name;
    vector<Room> rooms;
    vector<Customer> customers;
    Billing billing;
};

#endif
