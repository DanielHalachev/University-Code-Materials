//
// Created by User on 29.5.2021 г..
//

#include "Coke.hpp"

Coke::Coke(const double &quantity, const CokeType &type)
        : SoftDrink("Coca-Cola", quantity), type(type) {
}

CokeType Coke::getType() const {
    return this->type;
}

std::string Coke::toString() const {
    std::string cokeType;
    switch (this->type) {
        case 0:
            cokeType = "Classic";
            break;
        case 1:
            cokeType = "Light";
            break;
        default:
            cokeType = "None";
    }
    return this->brand + " " + cokeType + " (" + std::to_string(+this->alcoholPercentage) + " %:" +
           std::to_string(this->quantityInLitres) + "L";
}
