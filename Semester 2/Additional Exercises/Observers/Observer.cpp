//
// Created by User on 3.6.2021 г..
//

#include <iostream>
#include "Observer.hpp"

Observer::Observer(const std::string &name, const std::string &city, const double &temperature)
        : city(city), name(name), currentTemperature(temperature) {
}

void Observer::print() const {
    std::cout << this->name << ": The temperature in " << this->city << " is " << this->currentTemperature;
}
