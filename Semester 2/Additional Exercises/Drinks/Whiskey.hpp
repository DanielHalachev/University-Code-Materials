//
// Created by User on 29.5.2021 г..
//

#ifndef EXERCISES_WHISKEY_HPP
#define EXERCISES_WHISKEY_HPP


#include "Drink.hpp"

class Whiskey : public Drink {
public:
    Whiskey(const std::string &brand = "", const double &alcoholPercentage = 0, const double &quantity = 0,
            const unsigned int &age = 0);

private:
    unsigned int age;
};


#endif //EXERCISES_WHISKEY_HPP
