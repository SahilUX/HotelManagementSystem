#include "../include/Room.h"
#include <iostream>

Room::Room(int number, const string& type, const string& description)
    : number(number), type(type), description(description), available(true) {}

bool Room::isAvailable() const {
    return available;
}

void Room::book(const string& customerName, const string& fromDate) {
    available = false;
    bookedBy = customerName;
    this->fromDate = fromDate;
    this->toDate = "";
}

void Room::checkout() {
    available = true;
    bookedBy.clear();
    fromDate.clear();
    toDate.clear();
}

void Room::display() const {
    cout << "Room Number: " << number << ", Type: " << type << ", Description: " << description << endl;
}

void Room::displayroomnumbers() const {
    cout << "Room Number: " << number << endl;
}

int Room::getNumber() const {
    return number;
}

string Room::getType() const {
    return type;
}

double Room::getPrice() const {
    if (type == "Single") return 100.00;
    if (type == "Double") return 150.00;
    if (type == "King") return 200.00;
    if (type == "Suite") return 250.00;
    return 0.00;
}

string Room::getDescription() const {
    return description;
}
