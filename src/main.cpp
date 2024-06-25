#include <iostream>
#include <limits>
#include <regex>
#include "../include/Hotel.h"

using namespace std;

void displayMenu() {
    cout << "\nMoonlight Oasis Hotel Management System Menu:\n"
         << "1. Initialize System\n"
         << "2. Display Hotel Description\n"
         << "3. Check-in Customer\n"
         << "4. Check-out Customer\n"
         << "5. View Available Rooms\n"
         << "6. View Booked Rooms\n"
         << "7. View Rooms by Type\n"
         << "8. View Billing System\n"
         << "9. Save State\n"
         << "10. Exit\n"
         << "Enter your choice: ";
}

int getValidatedChoice() {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 10) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 10: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any extraneous input
            return choice;
        }
    }
}

int main() {
    Hotel hotel("Moonlight Oasis Hotel");
    int choice;
    string filename;

    while (true) {
        displayMenu();
        choice = getValidatedChoice();

        switch (choice) {
            case 1:
                cout << "Enter initialization file: ";
                cin >> filename;
                hotel.initialize(filename);
                break;
            case 2:
                hotel.displayDescription();
                break;
            case 3: {
                string name, fromDate;
                int roomNumber;
                cout << "Enter customer name: ";
                getline(cin, name);
                cout << "Enter from date (YYYY-MM-DD): ";
                while (true) {
                    cin >> fromDate;
                    regex dateRegex("\\d{4}-\\d{2}-\\d{2}");
                    if (cin && regex_match(fromDate, dateRegex)) {
                        break;
                    } else {
                        cout << "Invalid date format. Please enter a date in the format YYYY-MM-DD." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                cout << "Enter room number: ";
                cin >> roomNumber;
                hotel.checkIn(name, fromDate, roomNumber);
                break;
            }
            case 4: {
                int roomNumber;
                cout << "Enter room number: ";
                cin >> roomNumber;
                hotel.checkOut(roomNumber);
                break;
            }
            case 5:
                hotel.viewAvailableRooms();
                break;
            case 6:
                hotel.viewBookedRooms();
                break;
            case 7: {
                string type;
                cout << "Enter room type (Single Room, Double Room, King Room, Suite): ";
                getline(cin, type);
                hotel.viewRoomsByType(type);
                break;
            }
            case 8:
                hotel.viewBilling();
                break;
            case 9:
                cout << "Enter filename to save state: ";
                cin >> filename;
                hotel.saveState(filename);
                break;
            case 10:
                cout << "Exiting system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
