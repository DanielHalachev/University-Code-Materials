//
// Created by User on 8.6.2021 г..
//

#include <iostream>
#include "TShirt.hpp"

TShirt::TShirt(const std::string &name, const double &price, const std::string &color, const std::string &size)
        : StoreItem(name, T_SHIRT, price), color(color), size(size) {
}

TShirt *TShirt::clone() const {
    return new TShirt(*this);
}

std::string TShirt::getColor() const {
    return this->color;
}

std::string TShirt::getSize() const {
    return this->size;
}

void TShirt::setColor(const std::string &newColor) {
    this->color = newColor;
}

void TShirt::setSize(const std::string &newSize) {
    this->size = newSize;
}

bool TShirt::operator==(const TShirt &other) {
    return (this->color == other.color && this->size == other.size);
}
