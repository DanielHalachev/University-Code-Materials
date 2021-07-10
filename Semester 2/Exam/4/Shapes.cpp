//
// Daniel Halachev
// Clion GCC
//

#include <stdexcept>
#include "Shapes.hpp"

Shapes::Shapes(const Shapes &other) {
    for (auto shape:other.shapes) {
        this->shapes.push_back(shape->clone());
    }
}

Shapes &Shapes::operator=(const Shapes &other) {
    if (this != &other) {
        this->freeMemory();
        for (auto shape:other.shapes) {
            this->shapes.push_back(shape->clone());
        }
    }
    return *this;
}

Shapes::~Shapes() {
    this->freeMemory();
}

void Shapes::addCircle(Circle *circle) {
    this->shapes.push_back(circle->clone());
}

void Shapes::addRectangle(Rectangle *rectangle) {
    this->shapes.push_back(rectangle->clone());
}

void Shapes::addShape(const BaseShape *shape) {
    this->shapes.push_back(shape->clone());
}

bool Shapes::removeShape(const unsigned int &index) {
    // cannot remove non-existing shape
    if (index > this->shapes.size() - 1) {
        return false;
    }
    delete this->shapes[index];
    this->shapes.erase(this->shapes.begin() + index);
    return true;
}

double Shapes::getRectangleSizes() {
    double sizeSum = 0;
    // if the shape is a rectangle, add its size
    for (auto shape:this->shapes) {
        if (dynamic_cast<Rectangle *>(shape)) {
            sizeSum += shape->getSize();
        }
    }
    return sizeSum;
}

double Shapes::getCircleSizes() {
    double sizeSum = 0;
    // if the shape is a circle, add its size
    for (auto shape:this->shapes) {
        if (dynamic_cast<Circle *>(shape)) {
            sizeSum += shape->getSize();
        }
    }
    return sizeSum;
}

BaseShape *Shapes::getShape(const unsigned int &index) {
    if (index > this->shapes.size() - 1) {
        throw std::out_of_range("Invalid index");
    }
    return this->shapes[index];
}

void Shapes::freeMemory() {
    for (auto shape:this->shapes) {
        delete shape;
    }
}
