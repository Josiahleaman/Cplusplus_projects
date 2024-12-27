#pragma once
#include "Equipment.h"
#include <iomanip>

class Ladder : public Equipment {
    friend std::ostream& operator<<(std::ostream& os, const Ladder& ld);

private:
    float height;
    std::string style;
    int weightLimit;

public:
    Ladder(std::string id, double cost, Date date, int life, float h, std::string s, int w)
        : Equipment(id, cost, date, life), height(h), style(s), weightLimit(w) {
        if (h < 0 || w < 0)
            throw std::invalid_argument("Height and weight limit must be non-negative.");
    }

    // Getters and setters
    float getHeight() const { return height; }
    std::string getStyle() const { return style; }
    int getWeightLimit() const { return weightLimit; }
};

inline std::ostream& operator<<(std::ostream& os, const Ladder& ladder) {
    os << std::left << std::setw(20) << "ID number:" << ladder.getID() << "\n"
       << std::left << std::setw(20) << "Original cost:" << "$ " << std::fixed << std::setprecision(2) << ladder.getCost() << "\n"
       << std::left << std::setw(20) << "Date purchased:" << ladder.getPurchaseDate() << "\n"
       << std::left << std::setw(20) << "Useful life (in years):" << ladder.getUsefulLife() << "\n"
       << std::left << std::setw(20) << "Height:" << ladder.getHeight() << " feet\n"
       << std::left << std::setw(20) << "Style:" << ladder.getStyle() << "\n"
       << std::left << std::setw(20) << "Maximum weight limit:" << ladder.getWeightLimit() << " lbs\n";
    return os;
}