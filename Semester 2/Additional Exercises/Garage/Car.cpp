//
// Created by User on 4.6.2021 г..
//

#include "Car.hpp"

Car::Car(const std::string &brand, const std::string &model, const int &year, const std::string &problem,
         const ProblemSeverity &problemSeverity, bool isPrivate)
        : Vehicle(brand, model, year, problem, problemSeverity), isPrivate(isPrivate) {}

Car *Car::clone() const {
    return new Car(*this);
}
