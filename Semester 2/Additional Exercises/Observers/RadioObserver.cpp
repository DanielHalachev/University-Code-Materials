//
// Created by User on 3.6.2021 г..
//

#include <iostream>
#include "RadioObserver.hpp"

RadioObserver::RadioObserver(const std::string &name, const std::string &city, const double &temperature)
        : Observer(name, city, temperature) {

}

void RadioObserver::update(const std::string &city, const double &newTemperature) {
    this->city = city;
    this->currentTemperature = newTemperature;
    std::cout << "Update ";
    Observer::print();
}

void RadioObserver::printMeteo() const {
    std::cout << "Radio ";
    Observer::print();
}
