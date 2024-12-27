/*
Semester Project
main.cpp
This program is a storage unit system for WePaintHouses. It allows the user to manage two types of equipment: ladders and scaffolds.
The Equipment Storage System begins by defining a base class Equipment to represent common attributes such as ID, cost, purchaseDate,
and usefulLife, with dynamically allocated memory for ID managed through a copy constructor, destructor, and overloaded assignment operator.
Derived classes Ladder and Scaffold extend Equipment, adding unique attributes like height, weightLimit, and style. A class template
StorageUnit is created to handle storage for specific equipment types, with attributes such as unitID, dimensions, costPerMonth, and
additional details like rentalDate and autoRenew. Key functions include AddEquipment, ensuring unique IDs with exception handling, 
RemoveInventory, which confirms deletions, and PrintInventory, which sorts and displays equipment using overloaded operators. The main
function initializes two StorageUnit objects for ladders and scaffolds, manages a menu-driven system for user actions like updating storage 
information, adding/removing equipment, and printing inventory, and includes robust error handling and input validation. Finally, 
outputs are formatted neatly using alignment tools, and dynamic memory is properly managed to prevent leaks, ensuring a clean and 
efficient implementation.

Created by: Josiah Leaman
Create Date: 12/5/2024
*/
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Ladder.h"
#include "Scaffold.h"
#include "StorageUnit.h"
#include "Date.h"

using namespace std;

// Function Prototypes
void displayMainMenu();
void updateStorageUnitMenu(StorageUnit<Ladder>& ladderUnit, StorageUnit<Scaffold>& scaffoldUnit);
void addEquipmentToStorage(StorageUnit<Ladder>& ladderUnit, StorageUnit<Scaffold>& scaffoldUnit);
void removeEquipmentFromStorage(StorageUnit<Ladder>& ladderUnit, StorageUnit<Scaffold>& scaffoldUnit);
void printStorageInventory(const StorageUnit<Ladder>& ladderUnit, const StorageUnit<Scaffold>& scaffoldUnit);

// Utility function for input validation
template <typename T>
T getInput(const string& prompt);
Date getDateInput(const string& prompt); // New helper function for date input

// Specialized getInput<bool> to handle Y/N input
template <>
bool getInput<bool>(const string& prompt) {
    string input;
    cout << prompt;
    cin >> input;

    // Convert input to lowercase for consistency
    for (auto& c : input) c = tolower(c);

    if (input == "y" || input == "yes") {
        return true;
    } else if (input == "n" || input == "no") {
        return false;
    } else {
        cout << "Invalid input. Please enter Y or N.\n";
        return getInput<bool>(prompt); // Retry input
    }
}

int main() {
    // Create two StorageUnit objects: one for Ladders, one for Scaffolds
    StorageUnit<Ladder> ladderUnit("L1", "Ladder Storage Unit", 20.0, 10.0, 15.0, 500.0, Date(1, 1, 2023), true, true);
    StorageUnit<Scaffold> scaffoldUnit("S1", "Scaffold Storage Unit", 30.0, 20.0, 25.0, 800.0, Date(1, 1, 2023), true, false);

    int choice;
    do {
        displayMainMenu();
        choice = getInput<int>("Selection: ");
        switch (choice) {
            case 1:
                updateStorageUnitMenu(ladderUnit, scaffoldUnit);
                break;
            case 2:
                addEquipmentToStorage(ladderUnit, scaffoldUnit);
                break;
            case 3:
                removeEquipmentFromStorage(ladderUnit, scaffoldUnit);
                break;
            case 4:
                printStorageInventory(ladderUnit, scaffoldUnit);
                break;
            case 5:
                cout << "Exiting the program. Thank you for using WePaintHouses Storage System.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

// Display Main Menu
void displayMainMenu() {
    cout << "\n**************************************************\n";
    cout << "               WePaintHouses\n";
    cout << "         Equipment Storage System\n";
    cout << "**************************************************\n";
    cout << "\n    1 - Update Storage Unit General Information\n";
    cout << "    2 - Add Equipment to a Storage Unit\n";
    cout << "    3 - Remove Equipment from a Storage Unit\n";
    cout << "    4 - Print Equipment Inventory -- All Units\n";
    cout << "    5 - Exit Program\n\n";
}

// Update Storage Unit Menu
void updateStorageUnitMenu(StorageUnit<Ladder>& ladderUnit, StorageUnit<Scaffold>& scaffoldUnit) {
    cout << "\nEnter the type of equipment for the Storage Unit\n"
         << "1 - Ladders\n"
         << "2 - Scaffolds\n";
    int choice = getInput<int>("Selection: ");

    if (choice == 1) {
        cout << "Storage Unit General Information:\n";
        string unitID = getInput<string>("Enter the ID of the Storage Unit: ");
        cin.ignore(); // Clear newline from the buffer
        string description;
        cout << "Enter the description for the Storage Unit: ";
        getline(cin, description); // Allow multi-word input

        ladderUnit = StorageUnit<Ladder>(
            unitID,
            description,
            getInput<float>("Enter the length of the unit (in feet): "),
            getInput<float>("Enter the width of the unit (in feet): "),
            getInput<float>("Enter the height of the unit (in feet): "),
            getInput<double>("Enter the cost per month to rent the unit: "),
            getDateInput("Enter the date rented (mm/dd/yyyy): "),
            getInput<bool>("Does the contract auto-renew? (Y or N): "),
            getInput<bool>("Is the unit humidity-controlled? (Y or N): ")
        );
        cout << "Ladder Storage Unit updated successfully!\n";
    } else if (choice == 2) {
        string unitID = getInput<string>("Enter the ID of the Storage Unit: ");
        cin.ignore(); // Clear newline from the buffer
        string description;
        cout << "Enter the description for the Storage Unit: ";
        getline(cin, description); // Allow multi-word input

        scaffoldUnit = StorageUnit<Scaffold>(
            unitID,
            description,
            getInput<float>("Enter the length of the unit (in feet): "),
            getInput<float>("Enter the width of the unit (in feet): "),
            getInput<float>("Enter the height of the unit (in feet): "),
            getInput<double>("Enter the cost per month to rent the unit: "),
            getDateInput("Enter the date rented (mm/dd/yyyy): "),
            getInput<bool>("Does the contract auto-renew? (Y or N): "),
            getInput<bool>("Is the unit humidity-controlled? (Y or N): ")
        );
        cout << "Scaffold Storage Unit updated successfully!\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

// Add Equipment to Storage
void addEquipmentToStorage(StorageUnit<Ladder>& ladderUnit, StorageUnit<Scaffold>& scaffoldUnit) {
    cout << "\nAdd Equipment:\n"
         << "1 - Ladders\n"
         << "2 - Scaffolds\n";
    int choice = getInput<int>("Selection: ");
    try {
        if (choice == 1) {
            cout << "Enter the LADDER information\n";
            Ladder newLadder(
                getInput<string>("Enter the items ID number: "),
                getInput<double>("Enter the original cost of the item: "),
                getDateInput("Enter purchase date (mm/dd/yyyy): "),
                getInput<int>("Enter useful life of the item (in years): "),
                getInput<float>("Enter height of the ladder (in feet): "),
                getInput<string>("Enter style of the ladder: "),
                getInput<int>("Enter the maximum weight that the ladder can support (in pounds): ")
            );
            ladderUnit.addEquipment(newLadder);
            cout << "Ladder added successfully!\n";
        } else if (choice == 2) {
            cout << "Enter the SCAFFOLDS information\n";
            Scaffold newScaffold(
                getInput<string>("Enter ID: "),
                getInput<double>("Enter cost: "),
                getDateInput("Enter purchase date (mm/dd/yyyy): "),
                getInput<int>("Enter useful life (in years): "),
                getInput<float>("Enter length (in feet): "),
                getInput<float>("Enter width (in feet): "),
                getInput<float>("Enter height (in feet): "),
                getInput<int>("Enter weight limit (in pounds): ")
            );
            scaffoldUnit.addEquipment(newScaffold);
            cout << "Scaffold added successfully!\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } catch (const exception& ex) {
        cout << "Error: " << ex.what() << "\n";
    }
}

// Remove Equipment from Storage
void removeEquipmentFromStorage(StorageUnit<Ladder>& ladderUnit, StorageUnit<Scaffold>& scaffoldUnit) {
    cout << "\nRemove Equipment:\n"
         << "1 - Ladders\n"
         << "2 - Scaffolds\n";
    int choice = getInput<int>("Select the storage unit to remove equipment from: ");
    string id = getInput<string>("Enter the ID of the equipment to remove: ");
    try {
        if (choice == 1) {
            ladderUnit.removeEquipment(id);
            cout << "Ladder removed successfully!\n";
        } else if (choice == 2) {
            scaffoldUnit.removeEquipment(id);
            cout << "Scaffold removed successfully!\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } catch (const exception& ex) {
        cout << "Error: " << ex.what() << "\n";
    }
}

// Print Storage Inventory
void printStorageInventory(const StorageUnit<Ladder>& ladderUnit, const StorageUnit<Scaffold>& scaffoldUnit) {
    cout << "\nPrint Inventory:\n"
         << "1 - Ladders\n"
         << "2 - Scaffolds\n";
    int choice = getInput<int>("Select the storage unit to print inventory for: ");
    if (choice == 1) {
        ladderUnit.printInventory();
    } else if (choice == 2) {
        scaffoldUnit.printInventory();
    } else {
        cout << "Invalid choice.\n";
    }
}

// Template for Input Validation
template <typename T>
T getInput(const string& prompt) {
    T value;
    cout << prompt;
    cin >> value;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again.\n" << prompt;
        cin >> value;
    }
    return value;
}

// Helper function to parse and validate a date in mm/dd/yyyy format
Date getDateInput(const string& prompt) {
    string dateInput;
    int day, month, year;

    cout << prompt;
    cin >> dateInput;

    // Parse the input string (e.g., "12/15/2022")
    char delimiter;
    istringstream dateStream(dateInput);
    dateStream >> month >> delimiter >> day >> delimiter >> year;

    // Validate the input format and ranges
    if (dateStream.fail() || delimiter != '/' || month < 1 || month > 12 || day < 1 || day > 31 || year < 1) {
        throw invalid_argument("Invalid date format. Please use mm/dd/yyyy.");
    }

    // Create and return the Date object
    return Date(day, month, year);
}