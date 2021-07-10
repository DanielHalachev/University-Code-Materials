//
// Created by User on 8.6.2021 г..
//

#include "Shoes.hpp"

Shoes::Shoes(const std::string &name, const double &price, const std::string &color, const std::string &type,
             const int &size)
        : StoreItem(name, SHOES, price), color(color), size(size), type(type) {
}

Shoes *Shoes::clone() const {
    return new Shoes(*this);
}

std::string Shoes::getShoeType() const {
    return this->type;
}

std::string Shoes::getColor() const {
    return this->color;
}

int Shoes::getSize() const {
    return this->size;
}

void Shoes::setType(const std::string &newType) {
    this->type = newType;
}

void Shoes::setColor(const std::string &newColor) {
    this->color = newColor;
}

void Shoes::setSize(const int &newSize) {
    this->size = newSize;
}
