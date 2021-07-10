#pragma once

#include "drink.hpp"

class VendingMachine {
public:
    VendingMachine();

    VendingMachine(const VendingMachine &from);

    ~VendingMachine();

    VendingMachine &operator=(const VendingMachine &from);

    bool add_drink(const Drink &to_add);

    int buy_drink(const char *drink_name, const double money);

    double get_income() const;

    // Add whatever you deem needed here
private:
    double income;
    Drink **storage;
    unsigned int totalDrinks;

    int drinkExists(const char *drinkName) const;

    void DeleteMemory() const;
};
