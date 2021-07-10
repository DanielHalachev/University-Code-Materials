//
// Created by User on 4.6.2021 г..
//

#ifndef EXERCISES_GARAGE_HPP
#define EXERCISES_GARAGE_HPP


#define CAPACITY 10

#include <vector>
#include "Vehicle.hpp"

class Garage {
public:
    Garage();
    Garage(const Garage &other);
    Garage& operator=(const Garage &other);
    ~Garage();
    void addVehicle(const Vehicle* vehicle);
    bool hasCapacity()const;

private:
    std::vector<Vehicle*> vehicles;
    unsigned int usedCapacity;
};


#endif //EXERCISES_GARAGE_HPP
