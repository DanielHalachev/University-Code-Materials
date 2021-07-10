//
// Daniel Halachev
// Clion GCC
//
#include "BaseShape.hpp"

BaseShape::BaseShape(const std::string &color)
        : color(color) {
}

std::string BaseShape::getColor() const {
    return this->color;
}

void BaseShape::setColor(const std::string &newColor) {
    this->color = newColor;
}
