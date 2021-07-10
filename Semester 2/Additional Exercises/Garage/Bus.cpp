//
// Created by User on 4.6.2021 г..
//

#include "Bus.hpp"

Bus::Bus(const std::string &brand, const std::string &model, const int &year, const std::string &problem,
         const ProblemSeverity &problemSeverity, const bool &hasPassengers)
         :Vehicle(brand, model, year, problem, problemSeverity), hasPassengers(hasPassengers){
}

Bus *Bus::clone() const {
    return new Bus(*this);
}
