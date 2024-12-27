#pragma once
#include "Equipment.h"
#include <iomanip>

class Scaffold : public Equipment {
    friend std::ostream& operator<<(std::ostream& os, const Scaffold& sc);

private:
    float length, width, height;
    int weightLimit;

public:
    Scaffold(std::string id, double cost, Date date, int life, float l, float w, float h, int wl)
        : Equipment(id, cost, date, life), length(l), width(w), height(h), weightLimit(wl) {
        if (l < 0 || w < 0 || h < 0 || wl < 0)
            throw std::invalid_argument("Dimensions and weight limit must be non-negative.");
    }

    // Getters and setters
    float getLength() const { return length; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    int getWeightLimit() const { return weightLimit; }
};

inline std::ostream& operator<<(std::ostream& os, const Scaffold& scaffold) {
    os << std::left << std::setw(20) << "ID number:" << scaffold.getID() << "\n"
       << std::left << std::setw(20) << "Original cost:" << "$ " << std::fixed << std::setprecision(2) << scaffold.getCost() << "\n"
       << std::left << std::setw(20) << "Date purchased:" << scaffold.getPurchaseDate() << "\n"
       << std::left << std::setw(20) << "Useful life (in years):" << scaffold.getUsefulLife() << "\n"
       << std::left << std::setw(20) << "Length:" << scaffold.getLength() << " feet\n"
       << std::left << std::setw(20) << "Width:" << scaffold.getWidth() << " feet\n"
       << std::left << std::setw(20) << "Height:" << scaffold.getHeight() << " feet\n"
       << std::left << std::setw(20) << "Maximum weight limit:" << scaffold.getWeightLimit() << " lbs\n";
    return os;
}