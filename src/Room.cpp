#include "../include/Room.h"
#include <iostream>
#include <locale>
#include <algorithm>

using namespace std;

// Helper function to trim whitespace from a string
static string trim(const string &s) {
    auto start = s.begin();
    while (start != s.end() && isspace(*start)) {
        start++;
    }

    auto end = s.end();
    do {
        end--;
    } while (distance(start, end) > 0 && isspace(*end));
    return string(start, end + 1);
}

// Helper function to convert a string to lowercase
static string toLower(const string &s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return tolower(c); });
    return result;
}

// Constructor for Room class
Room::Room(int number, const string& type, const string& description)
    : number(number), type(type), description(description), available(true) {}

// Check if the room is available
bool Room::isAvailable() const {
    return available;
}

// Book the room for a customer
void Room::book(const string& customerName, const string& fromDate) {
    available = false;
    bookedBy = customerName;
    this->fromDate = fromDate;
    this->toDate = "";
}

// Check out the room
void Room::checkout() {
    available = true;
    bookedBy.clear();
    fromDate.clear();
    toDate.clear();
}

// Display the room details
void Room::display() const {
    if (type == "suite") {
        cout << "Room Number: " << number << ", Type: " << type << ", Description: " << description << endl;
    } else {
        cout << "Room Number: " << number << ", Type: " << type << " room, Description: " << description << endl;
    }
}

// Display room details without description
void Room::displaynodesc() const {
    cout << "Room Number: " << number << ", Type: " << type << endl;
}

// Display room details along with customer information if booked
void Room::displayWithCustomer() const {
    cout << "Room Number: " << number << ", Type: " << type;
    if (!available) {
        cout << ", Booked By: " << bookedBy << ", From Date: " << fromDate;
    }
    cout << endl;
}

// Get the room number
int Room::getNumber() const {
    return number;
}

// Get the room type
string Room::getType() const {
    string trimmedType = trim(type);
    string lowerType = toLower(trimmedType);
    return lowerType;
}

// Get the room description
string Room::getDescription() const {
    return description;
}

// Get the name of the customer who booked the room
string Room::getBookedBy() const {
    return bookedBy;
}

// Get the price of the room based on type
double Room::getPrice() const {
    string trimmedType = trim(type);
    string lowerType = toLower(trimmedType);

    if (lowerType == "single") return 100.00;
    if (lowerType == "double") return 150.00;
    if (lowerType == "king") return 200.00;
    if (lowerType == "suite") return 250.00;

    return 0.00;
}
