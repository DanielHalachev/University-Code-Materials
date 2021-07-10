//
// Daniel Halachev
// Clion GCC
//

#include "Circle.hpp"

Circle::Circle(const double &radius, const std::string &color)
        : BaseShape(color), radius(radius) {
}

double Circle::getRadius() const {
    return this->radius;
}

void Circle::setRadius(const double &newRadius) {
    this->radius = newRadius;
}

double Circle::getSize() const {
    // S=pi*(r)^2
    return PI * (this->radius * this->radius);

}

Circle *Circle::clone() const {
    return new Circle(*this);
}
