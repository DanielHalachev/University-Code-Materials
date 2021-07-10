//
// Created by User on 4.6.2021 г..
//

#ifndef EXERCISES_BUS_HPP
#define EXERCISES_BUS_HPP


#include "Vehicle.hpp"

class Bus: public Vehicle {
public:
    Bus(const std::string &brand="", const std::string &model="", const int &year=2000, const std::string &problem ="", const ProblemSeverity &problemSeverity=AVERAGE, const bool &hasPassengers=true);
    Bus* clone()const override;
private:
    bool hasPassengers;
};


#endif //EXERCISES_BUS_HPP
