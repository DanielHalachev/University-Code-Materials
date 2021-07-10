//
// Created by User on 4.6.2021 г..
//

#ifndef EXERCISES_CAR_HPP
#define EXERCISES_CAR_HPP


#include "Vehicle.hpp"

class Car: public Vehicle {
public:
    Car(const std::string &brand="", const std::string &model="", const int &year=2000, const std::string &problem ="", const ProblemSeverity &problemSeverity=AVERAGE, bool isPrivate=true);
    Car* clone()const override;
private:
    bool isPrivate;
};


#endif //EXERCISES_CAR_HPP
