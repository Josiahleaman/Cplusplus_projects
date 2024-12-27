#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include "Date.h"

class Equipment {
    friend std::ostream& operator<<(std::ostream& os, const Equipment& eq);

protected:
    std::string* id;
    double originalCost;
    int usefulLife;
    Date purchaseDate;

public:
    Equipment(std::string id, double cost, Date date, int life)
        : id(new std::string(id)), originalCost(cost), purchaseDate(date), usefulLife(life) {
        if (cost < 0 || life < 0)
            throw std::invalid_argument("Cost and useful life must be non-negative.");
    }

    // Copy Constructor
    Equipment(const Equipment& other)
        : id(new std::string(*other.id)), originalCost(other.originalCost),
          purchaseDate(other.purchaseDate), usefulLife(other.usefulLife) {}

    // Assignment Operator
    Equipment& operator=(const Equipment& other) {
        if (this == &other) return *this;
        delete id;
        id = new std::string(*other.id);
        originalCost = other.originalCost;
        purchaseDate = other.purchaseDate;
        usefulLife = other.usefulLife;
        return *this;
    }

    // Destructor
    virtual ~Equipment() { delete id; }

    // Overload < for sorting by ID
    bool operator<(const Equipment& other) const { return *id < *other.id; }

    // Getters and setters
    std::string getID() const { return *id; }
    double getCost() const { return originalCost; }
    int getUsefulLife() const { return usefulLife; }
    Date getPurchaseDate() const { return purchaseDate; }
};

inline std::ostream& operator<<(std::ostream& os, const Equipment& eq) {
    os << "ID: " << *eq.id << ", Cost: $" << eq.originalCost << ", Date: " << eq.purchaseDate
       << ", Useful Life: " << eq.usefulLife << " years";
    return os;
}
