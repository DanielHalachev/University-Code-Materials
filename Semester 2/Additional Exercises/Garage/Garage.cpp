//
// Created by User on 4.6.2021 г..
//

#include "Garage.hpp"

Garage::Garage(const Garage &other) {
    this->usedCapacity = other.usedCapacity;
    for (auto vehicle:other.vehicles) {
        this->vehicles.push_back(vehicle->clone());
    }
}

Garage &Garage::operator=(const Garage &other) {
    if (this != &other) {
        this->usedCapacity = other.usedCapacity;
        for (auto vehicle: this->vehicles) {
            delete vehicle;
        }
        for (auto vehicle:other.vehicles) {
            this->vehicles.push_back(vehicle->clone());
        }
    }
    return *this;
}

Garage::~Garage() {
    for (auto vehicle:this->vehicles) {
        delete vehicle;
    }
}

void Garage::addVehicle(const Vehicle *vehicle) {
    int points = 0;
    switch (vehicle->getSeverity()) {
        case LOW:
            points += 1;
            break;
        case AVERAGE:
            points += 2;
            break;
        case HIGH:
            points += 3;
            break;
        default:
            points += 0;
    }
    if (this->usedCapacity + points <= CAPACITY) {
        this->vehicles.push_back(vehicle->clone());
        this->usedCapacity += points;
    }
}

bool Garage::hasCapacity() const {
    return (this->usedCapacity < 11);
}

Garage::Garage() {
    this->usedCapacity = 0;
}
