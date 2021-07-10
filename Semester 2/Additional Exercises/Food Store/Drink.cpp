//
// Created by User on 14.6.2021 г..
//

#include "Drink.hpp"

Drink::Drink(const std::string &name, const std::string &code, const double &price, const double &alcoholPercentage)
        : StoreProduct(name, code, price), alcoholPercentage(alcoholPercentage) {
}

Drink *Drink::clone() const {
    return new Drink(*this);
}

void Drink::print(std::ostream &out) const {
    out << this->name << ", " << this->code << ", " << this->price << ", " << this->alcoholPercentage << "%";
}
