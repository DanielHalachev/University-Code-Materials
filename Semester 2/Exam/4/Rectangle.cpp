//
// Daniel Halachev
// Clion GCC
//

#include "Rectangle.hpp"

Rectangle::Rectangle(const double &width, const double &height, const std::string &color)
        : BaseShape(color), width(width), height(height) {
}

double Rectangle::getWidth() const {
    return this->width;
}

double Rectangle::getHeight() const {
    return this->height;
}

void Rectangle::setWidth(const double &newWidth) {
    this->width = newWidth;
}

void Rectangle::setHeight(const double &newHeight) {
    this->height = newHeight;
}

double Rectangle::getSize() const {
    return this->width * this->height;
}

Rectangle *Rectangle::clone() const {
    return new Rectangle(*this);
}
