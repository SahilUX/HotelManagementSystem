#include "../include/Hotel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <limits>

using namespace std;

// Function to validate if a given date is valid
bool isValidDate1(int year, int month, int day) {
    if (year < 2024) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;
    const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap && day <= 29) return true;
        if (!isLeap && day <= 28) return true;
    } else {
        if (day <= daysInMonth[month - 1]) return true;
    }
    return false;
}

// Constructor to initialize the hotel with a name
Hotel::Hotel(const string& name) : name(name) {}

// Initializes the hotel system from a file
void Hotel::initialize(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    // Check if the file is empty
    if (file.peek() == ifstream::traits_type::eof()) {
        cerr << "Error: Initialization file " << filename << " is empty." << endl;
        file.close();
        return;
    }

    rooms.clear();
    billing.clear();
    customers.clear();

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string type;
        iss >> type;
        if (type == "ROOM") {
            int roomNumber;
            string roomType, description;
            iss >> roomNumber >> roomType;
            getline(iss, description, '"');
            getline(iss, description, '"');
            rooms.emplace_back(roomNumber, roomType, description);
        } else if (type == "CUSTOMER") {
            string name, fromDate, toDate;
            int roomNumber;
            iss >> ws;
            getline(iss, name, ' ');
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
            string name, details;
            double amount;
            iss >> ws;
            getline(iss, name, ' ');
            iss >> amount;
            getline(iss, details);
            for (const auto& customer : customers) {
                if (customer.getName() == name) {
                    billing.addBill(customer, customer.getRoomNumber(), amount, details);
                    break;
                }
            }
        }
    }

    file.close();
    cout << "System initialized from " << filename << endl;
}

// Displays the hotel description
void Hotel::displayDescription() const {
    cout << "Hotel Name: " << name << endl;
    cout << "Rooms Information: " << endl;
    for (const auto& room : rooms) {
        room.displaynodesc();
    }
}

// Checks in a customer to a room
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

// Checks out a customer from a room
void Hotel::checkOut(int roomNumber) {
    auto it = find_if(rooms.begin(), rooms.end(), [roomNumber](const Room& room) {
        return room.getNumber() == roomNumber;
    });

    if (it != rooms.end() && !it->isAvailable()) {
        string toDate;
        cout << "Enter check-out date (YYYY-MM-DD): ";
        while (true) {
            cin >> toDate;
            regex dateRegex(R"(\d{4}-(1[0-2]|0[1-9])-(3[01]|[12][0-9]|0[1-9]))");
            if (cin && regex_match(toDate, dateRegex)) {
                int year, month, day;
                sscanf(toDate.c_str(), "%d-%d-%d", &year, &month, &day);
                if (isValidDate1(year, month, day)) {
                    break;
                } else {
                    cout << "Invalid date. Please enter a valid date in the format YYYY-MM-DD." << endl;
                }
            } else {
                cout << "Invalid date format. Please enter a date in the format YYYY-MM-DD." << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        auto custIt = find_if(customers.begin(), customers.end(), [roomNumber](const Customer& customer) {
            return customer.getRoomNumber() == roomNumber;
        });

        if (custIt != customers.end()) {
            custIt->setCheckOutDate(toDate);
            int daysStayed = custIt->calculateDaysStayed();
            double roomPrice = it->getPrice();
            double amount = daysStayed * roomPrice;
            billing.addBill(*custIt, roomNumber, amount, "Room stay for " + to_string(daysStayed) + " days");
        }

        it->checkout();
        cout << "Customer checked out from room " << roomNumber << endl;
    } else {
        cout << "Room " << roomNumber << " is not currently booked." << endl;
    }
}

// Views all available rooms
void Hotel::viewAvailableRooms() const {
    cout << "Available Rooms: " << endl;
    for (const auto& room : rooms) {
        if (room.isAvailable()) {
            room.display();
        }
    }
}

// Views all booked rooms
void Hotel::viewBookedRooms() const {
    cout << "Booked Rooms: " << endl;
    for (const auto& room : rooms) {
        if (!room.isAvailable()) {
            room.displayWithCustomer();
        }
    }
}

// Views rooms by their type
void Hotel::viewRoomsByType(const string& type) const {
    cout << "Rooms of Type: " << type << endl;
    for (const auto& room : rooms) {
        if (room.getType() == type) {
            room.display();
        }
    }
}

// Views the billing information
void Hotel::viewBilling() const {
    billing.display();
}

// Saves the current state of the hotel system to a file
void Hotel::saveState(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    for (const auto& room : rooms) {
        file << "ROOM " << room.getNumber() << " " << room.getType() << " \"" << room.getDescription() << "\"\n";
    }

    for (const auto& customer : customers) {
        file << "CUSTOMER " << customer.getName() << " " << customer.getCheckInDate() << " " << customer.getCheckOutDate() << " " << customer.getRoomNumber() << "\n";
    }

    for (const auto& bill : billing.getBills()) {
        file << "BILL " << bill.customer.getName() << " " << bill.amount << " " << bill.details << "\n";
    }

    file.close();
    cout << "System state saved to " << filename << endl;
}
