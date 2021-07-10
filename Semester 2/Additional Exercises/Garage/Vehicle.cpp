//
// Created by User on 4.6.2021 г..
//

#include "Vehicle.hpp"

Vehicle::Vehicle(const std::string &brand, const std::string &model, const int &year, const std::string &problem,
                 const ProblemSeverity &problemSeverity)
        : brand(brand), model(model), yearOfProduction(year), problem(problem), severity(problemSeverity) {
}

ProblemSeverity Vehicle::getSeverity() const {
    return this->severity;
}

Vehicle *Vehicle::clone()const {
    return new Vehicle(*this);
}
