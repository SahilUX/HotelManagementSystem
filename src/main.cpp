#include <iostream>
#include <limits>
#include <regex>
#include <iomanip>
#include <string>
#include "../include/Hotel.h"

using namespace std;

// Function to validate if a given date is valid
bool isValidDate(int year, int month, int day) {
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

// Function to display the menu
void displayMenu() {
    cout << "\nManagement System Menu:\n\n";
    cout << setw(6) << left << "" << "1. Initialize System\n"
         << setw(6) << left << "" << "2. Display Hotel Description\n"
         << setw(6) << left << "" << "3. Check-in Customer\n"
         << setw(6) << left << "" << "4. Check-out Customer\n"
         << setw(6) << left << "" << "5. View Available Rooms\n"
         << setw(6) << left << "" << "6. View Booked Rooms\n"
         << setw(6) << left << "" << "7. View Rooms by Type\n"
         << setw(6) << left << "" << "8. View Billing System\n"
         << setw(6) << left << "" << "9. Save State\n"
         << setw(5) << left << "" << "10. Exit\n\n";
    cout << "Enter your choice: ";
}

// Function to get a valid choice from the user
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
    cout << "Welcome to Moonlight Oasis Hotel" << endl;
    int choice;
    string filename;

    while (true) {
        displayMenu();
        choice = getValidatedChoice();

        switch (choice) {
            case 1: {
                int choice1;
                cout << "Would you like to: \n";
                cout << "1. Initialize from scratch\n";
                cout << "2. Initialize from last saved state\n";
                cout << "Enter your choice: ";
                cin >> choice1;
                if (choice1 == 1) {
                    filename = "../data/hotel_data.txt";
                } else if (choice1 == 2) {
                    filename = "../data/hotel_data_saved_state.txt";
                } else {
                    cout << "Invalid choice. Please enter 1 or 2.\n";
                    continue;
                }
                hotel.initialize(filename);
                break;
            }
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
                    regex dateRegex("\\d{4}-(1[0-2]|0[1-9])-(3[01]|[12][0-9]|0[1-9])");
                    if (cin && regex_match(fromDate, dateRegex)) {
                        int year, month, day;
                        sscanf(fromDate.c_str(), "%d-%d-%d", &year, &month, &day);
                        if (isValidDate(year, month, day)) {
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
                cout << "Enter room number: ";
                cin >> roomNumber;
                hotel.checkIn(name, fromDate, roomNumber);
                break;
            }
            case 4: {
                int roomNumber;
                hotel.viewBookedRooms();
                cout << "Enter room number to check-out: ";
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
                int num;
                string type;
                cout << "Enter room type (1. Single Room, 2. Double Room, 3. King Room, 4. Suite): ";
                cin >> num;
                switch (num) {
                    case 1:
                        type = "single";
                        break;
                    case 2:
                        type = "double";
                        break;
                    case 3:
                        type = "king";
                        break;
                    case 4:
                        type = "suite";
                        break;
                    default:
                        cout << "Invalid room type. Please enter 1, 2, 3 or 4." << endl;
                        continue;
                }
                hotel.viewRoomsByType(type);
                break;
            }
            case 8:
                hotel.viewBilling();
                break;
            case 9:
                hotel.saveState("../data/hotel_data_saved_state.txt");
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
