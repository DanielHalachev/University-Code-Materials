//
// Created by User on 29.5.2021 г..
//

#include "Drink.hpp"

Drink::Drink(const std::string &brand, const double &alcoholPercentage, const double &quantity)
        : brand(brand), alcoholPercentage(alcoholPercentage), quantityInLitres(quantity) {
}

std::string Drink::getBrand() const {
    return this->brand;
}

double Drink::getPercentage() const {
    return this->alcoholPercentage;
}

double Drink::getQuantity() const {
    return this->quantityInLitres;
}

void Drink::add(const double &quantity) {
    this->quantityInLitres += quantity;
}

void Drink::remove(const double &quantity) {
    if (this->quantityInLitres >= quantity) {
        this->quantityInLitres -= quantity;
    }
}

std::string Drink::toString() const {
    return this->brand + " (" + std::to_string(+this->alcoholPercentage) + " %:" +
           std::to_string(this->quantityInLitres) + "L";
}
