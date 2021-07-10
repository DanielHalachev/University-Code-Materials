//
// Created by User on 8.6.2021 г..
//

#include <iostream>
#include "StoreItem.hpp"

StoreItem::StoreItem(const std::string &name, const ProductType &productType, const double &price)
        : name(name), productType(productType), price(price) {
}

std::string StoreItem::getName() const {
    return this->name;
}

ProductType StoreItem::getType() const {
    return this->productType;
}

double StoreItem::getPrice() const {
    return this->price;
}

void StoreItem::setName(const std::string &newName) {
    this->name = newName;
}

void StoreItem::setType(const ProductType &type) {
    this->productType = type;
}

void StoreItem::setPrice(const double &newPrice) {
    this->price = newPrice;
}

void StoreItem::print() const {
    std::string type;
    switch (this->productType) {
        case T_SHIRT:
            type = "T-Shirt ";
            break;
        case SHOES:
            type = "Shoes ";
            break;
        default:
            type = "Store Item ";
    }
    std::cout << type << this->name << ", " << this->price << std::endl;
}
