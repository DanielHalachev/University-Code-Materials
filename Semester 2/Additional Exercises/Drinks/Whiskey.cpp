//
// Created by User on 29.5.2021 г..
//

#include "Whiskey.hpp"

Whiskey::Whiskey(const std::string &brand, const double &alcoholPercentage, const double &quantity,
                 const unsigned int &age)
        : Drink(brand, alcoholPercentage, quantity), age(age) {
}
