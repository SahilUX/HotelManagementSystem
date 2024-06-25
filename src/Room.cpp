#include "../include/Room.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>

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

// Helper function to trim whitespace from both ends of a string
static inline std::string trim(const std::string &s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        start++;
    }

    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

// Helper function to convert a string to lowercase
static inline std::string toLower(const std::string &s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}

double Room::getPrice() const {
    std::string trimmedType = trim(type);
    std::string lowerType = toLower(trimmedType);

    if (lowerType == "single") return 100.00;
    if (lowerType == "double") return 150.00;
    if (lowerType == "king") return 200.00;
    if (lowerType == "suite") return 250.00;

    return 0.00;
}
string Room::getDescription() const {
    return description;
}
