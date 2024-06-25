#ifndef ROOM_H
#define ROOM_H

#include <string>

using namespace std;

class Room {
public:
    Room(int number, const string& type, const string& description);
    bool isAvailable() const;
    void book(const string& customerName, const string& fromDate);
    void checkout();
    void display() const;
    void displayroomnumbers() const;

    int getNumber() const;
    string getType() const;
    double getPrice() const;
    string getDescription() const;

private:
    int number;
    string type;
    string description;
    bool available;
    string bookedBy;
    string fromDate;
    string toDate;
};

#endif
