//
// Created by User on 29.5.2021 г..
//

#include "NonAlcoholicBeer.hpp"

NonAlcoholicBeer::NonAlcoholicBeer(const std::string &brand, const double &quantity)
        : SoftDrink(brand, quantity), Beer(brand, 0, quantity, false, OTHER) {

}
