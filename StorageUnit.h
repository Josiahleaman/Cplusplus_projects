#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Date.h"
#include <iomanip>

template <typename T>
class StorageUnit {
private:
    std::string unitID;
    std::string description;  // Description of the storage unit
    float length, width, height;
    double rentCost;
    Date rentalDate;
    bool autoRenew;
    bool humidityControlled;
    std::vector<T> inventory;

public:
    // Constructor
    StorageUnit(const std::string& id, const std::string& desc, float l, float w, float h, double cost, 
                const Date& date, bool renew, bool humidity)
        : unitID(id), description(desc), length(l), width(w), height(h), rentCost(cost), 
          rentalDate(date), autoRenew(renew), humidityControlled(humidity) {}

    // Default Constructor
    StorageUnit() : unitID(""), description(""), length(0), width(0), height(0), rentCost(0), 
                    rentalDate(Date()), autoRenew(false), humidityControlled(false) {}

    // Getters and Setters
    void setUnitID(const std::string& id) { unitID = id; }
    std::string getUnitID() const { return unitID; }

    void setDescription(const std::string& desc) { description = desc; }
    std::string getDescription() const { return description; }

    void setLength(float l) { length = l; }
    float getLength() const { return length; }

    void setWidth(float w) { width = w; }
    float getWidth() const { return width; }

    void setHeight(float h) { height = h; }
    float getHeight() const { return height; }

    void setRentCost(double cost) { rentCost = cost; }
    double getRentCost() const { return rentCost; }

    void setRentalDate(const Date& date) { rentalDate = date; }
    Date getRentalDate() const { return rentalDate; }

    void setAutoRenew(bool renew) { autoRenew = renew; }
    bool getAutoRenew() const { return autoRenew; }

    void setHumidityControlled(bool humidity) { humidityControlled = humidity; }
    bool getHumidityControlled() const { return humidityControlled; }

    void addEquipment(const T& equipment) {
        for (const auto& item : inventory) {
            if (item.getID() == equipment.getID()) {
                throw std::invalid_argument("Duplicate equipment ID is not allowed.");
            }
        }
        inventory.push_back(equipment);
    }

    void removeEquipment(const std::string& id) {
        auto it = std::find_if(inventory.begin(), inventory.end(), [&id](const T& item) {
            return item.getID() == id;
        });
        if (it == inventory.end()) {
            throw std::invalid_argument("Equipment ID not found.");
        }
        inventory.erase(it);
    }

    // Print Inventory
    void printInventory() const {
        using namespace std;

        cout << "\n**************************************************\n";
        cout << "               Storage Unit Information\n";
        cout << "**************************************************\n";

        // General Information
        cout << left << setw(20) << "Unit ID:" << unitID << "\n";
        cout << left << setw(20) << "Description:" << description << "\n";
        cout << "Dimensions\n";
        cout << left << setw(20) << "  Length:" << length << " feet\n";
        cout << left << setw(20) << "  Width:" << width << " feet\n";
        cout << left << setw(20) << "  Height:" << height << " feet\n";
        cout << "\n";

        cout << "**Unit is " << (humidityControlled ? "humidity controlled." : "not humidity controlled.") << "\n\n";

        cout << "Rental Contract\n";
        cout << left << setw(20) << "  Cost Per Month:" << "$ " << fixed << setprecision(2) << rentCost << "\n";
        cout << left << setw(20) << "  Date Signed:" << rentalDate << "\n";
        cout << "**Contract " << (autoRenew ? "does auto-renew." : "does not auto-renew.") << "\n";

        cout << "**************************************************\n";
        cout << "**************************************************\n";

        // Inventory
        if (inventory.empty()) {
            cout << "No items in inventory.\n";
        } else {
            for (const auto& item : inventory) {
                cout << "--------------------------------------------------\n";
                cout << item; // Overloaded << operator for Equipment-derived objects
                cout << "\n";
            }
        }

        cout << "**************************************************\n";
    }
};