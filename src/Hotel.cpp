#include "../include/Hotel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <regex>
#include <limits>

using namespace std;

Hotel::Hotel(const string& name) : name(name) {}

void Hotel::initialize(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    rooms.clear();
    customers.clear();
    billing.clear();

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string type;
        iss >> type;
        if (type == "ROOM") {
            int roomNumber;
            string roomType;
            string description;
            iss >> roomNumber;
            iss.ignore();
            getline(iss, roomType, '"');
            getline(iss, description, '"');
            rooms.emplace_back(roomNumber, roomType, description);
        } else if (type == "CUSTOMER") {
            string name, fromDate, toDate;
            int roomNumber;
            iss >> ws;
            getline(iss, name, ',');
            iss >> fromDate >> toDate >> roomNumber;
            Customer customer(name, fromDate, roomNumber);
            customer.setCheckOutDate(toDate);
            customers.push_back(customer);

            auto roomIt = find_if(rooms.begin(), rooms.end(), [roomNumber](const Room& room) {
                return room.getNumber() == roomNumber;
            });
            if (roomIt != rooms.end()) {
                roomIt->book(name, fromDate);
            }
        } else if (type == "BILL") {
            string name;
            double amount;
            string details;
            iss >> ws;
            getline(iss, name, ',');
            iss >> amount;
            getline(iss, details);
            for (const auto& customer : customers) {
                if (customer.getName() == name) {
                    billing.addBill(customer, amount, details);
                    break;
                }
            }
        }
    }

    file.close();
    cout << "System initialized from " << filename << endl;
}

void Hotel::displayDescription() const {
    cout << "Hotel Name: " << name << endl;
    cout << "Rooms Information: " << endl;
    for (const auto& room : rooms) {
        room.displayroomnumbers();
    }
}

void Hotel::checkIn(const string& customerName, const string& fromDate, int roomNumber) {
    auto it = find_if(rooms.begin(), rooms.end(), [roomNumber](const Room& room) {
        return room.getNumber() == roomNumber;
    });

    if (it != rooms.end() && it->isAvailable()) {
        it->book(customerName, fromDate);
        customers.emplace_back(customerName, fromDate, roomNumber);
        cout << "Customer " << customerName << " checked into room " << roomNumber << endl;
    } else {
        cout << "Room " << roomNumber << " is not available for booking." << endl;
    }
}

void Hotel::checkOut(int roomNumber) {
    auto it = find_if(rooms.begin(), rooms.end(), [roomNumber](const Room& room) {
        return room.getNumber() == roomNumber;
    });

    if (it != rooms.end() && !it->isAvailable()) {
        string toDate;
        cout << "Enter check-out date (YYYY-MM-DD): ";
        while (true) {
            cin >> toDate;
            regex dateRegex("\\d{4}-\\d{2}-\\d{2}");
            if (cin && regex_match(toDate, dateRegex)) {
                break;
            } else {
                cout << "Invalid date format. Please enter a date in the format YYYY-MM-DD." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        auto custIt = find_if(customers.begin(), customers.end(), [roomNumber](const Customer& customer) {
            return customer.getRoomNumber() == roomNumber;
        });

        if (custIt != customers.end()) {
            custIt->setCheckOutDate(toDate);
            int daysStayed = custIt->calculateDaysStayed();
            double amount = daysStayed * it->getPrice();
            billing.addBill(*custIt, amount, "Room stay for " + to_string(daysStayed) + " days");
        }

        it->checkout();
        cout << "Customer checked out from room " << roomNumber << endl;
    } else {
        cout << "Room " << roomNumber << " is not currently booked." << endl;
    }
}

void Hotel::viewAvailableRooms() const {
    cout << "Available Rooms: " << endl;
    for (const auto& room : rooms) {
        if (room.isAvailable()) {
            room.display();
        }
    }
}

void Hotel::viewBookedRooms() const {
    cout << "Booked Rooms: " << endl;
    for (const auto& room : rooms) {
        if (!room.isAvailable()) {
            room.display();
        }
    }
}

void Hotel::viewRoomsByType(const string& type) const {
    cout << "Rooms of Type: " << type << endl;
    for (const auto& room : rooms) {
        if (room.getType() == type) {
            room.display();
        }
    }
}

void Hotel::viewBilling() const {
    cout << "Billing Information: " << endl;
    billing.display();
}

void Hotel::saveState(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    for (const auto& room : rooms) {
        file << "ROOM " << room.getNumber() << " " << room.getType() << " " << room.getDescription() << "\n";
    }

    for (const auto& customer : customers) {
        file << "CUSTOMER " << customer.getName() << "," << customer.getCheckInDate() << " " << customer.getCheckOutDate() << " " << customer.getRoomNumber() << "\n";
    }

    for (const auto& bill : billing.getBills()) {
        file << "BILL " << bill.customer.getName() << "," << bill.amount << " " << bill.details << "\n";
    }

    file.close();
    cout << "System state saved to " << filename << endl;
}
