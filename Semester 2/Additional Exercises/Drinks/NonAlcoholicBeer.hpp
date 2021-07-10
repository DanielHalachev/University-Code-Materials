//
// Created by User on 29.5.2021 г..
//

#ifndef EXERCISES_NONALCOHOLICBEER_HPP
#define EXERCISES_NONALCOHOLICBEER_HPP


#include "Beer.hpp"
#include "SoftDrink.hpp"

class NonAlcoholicBeer : public virtual SoftDrink, public virtual Beer {
    explicit NonAlcoholicBeer(const std::string &brand, const double &quantity = 0);
};


#endif //EXERCISES_NONALCOHOLICBEER_HPP
