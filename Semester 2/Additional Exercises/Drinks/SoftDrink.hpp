//
// Created by User on 29.5.2021 г..
//

#ifndef EXERCISES_SOFTDRINK_HPP
#define EXERCISES_SOFTDRINK_HPP


#include "Drink.hpp"

class SoftDrink : public virtual Drink {
public:
    SoftDrink(const std::string &brand = "", const double &quantity = 0);
};


#endif //EXERCISES_SOFTDRINK_HPP
