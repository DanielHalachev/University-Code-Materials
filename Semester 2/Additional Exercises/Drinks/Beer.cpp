//
// Created by User on 29.5.2021 г..
//

#include "Beer.hpp"

Beer::Beer(const std::string &brand, const double &alcoholPercentage, const double &quantity, const bool &isCraft,
           const BeerType &type)
        : Drink(brand, alcoholPercentage, quantity), isCraft(isCraft), type(type) {

}
