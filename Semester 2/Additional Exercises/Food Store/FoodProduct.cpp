//
// Created by User on 14.6.2021 г..
//

#include "FoodProduct.hpp"

FoodProduct::FoodProduct(const std::string &name, const std::string &code, const double &price,
                         const unsigned int &calories)
        : StoreProduct(name, code, price), calories(calories) {
}

FoodProduct *FoodProduct::clone() const {
    return new FoodProduct(*this);
}

void FoodProduct::print(std::ostream &out) const {
    out << this->name << ", " << this->code << ", " << this->price << ", " << this->calories;
}
