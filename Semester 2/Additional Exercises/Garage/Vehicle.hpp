//
// Created by User on 4.6.2021 г..
//

#ifndef EXERCISES_VEHICLE_HPP
#define EXERCISES_VEHICLE_HPP


#include <string>
enum ProblemSeverity{LOW, AVERAGE, HIGH};
class Vehicle {
public:
    Vehicle(const std::string &brand="", const std::string &model="", const int &year=2000, const std::string &problem ="", const ProblemSeverity &problemSeverity=AVERAGE);
    ProblemSeverity getSeverity()const;
    virtual Vehicle* clone()const;
protected:
    std::string brand;
    std::string model;
    int yearOfProduction;
    std::string problem;
    ProblemSeverity severity;
};


#endif //EXERCISES_VEHICLE_HPP
