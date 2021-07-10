//
// Created by User on 3.6.2021 г..
//

#include <iostream>
#include "NewspaperObserver.hpp"

NewspaperObserver::NewspaperObserver(const std::string &name, const std::string &city, const double &temperature)
        : Observer(name, city, temperature) {
}

void NewspaperObserver::update(const std::string &city, const double &newTemperature) {
    this->city = city;
    this->currentTemperature = newTemperature;
    std::cout << "Update ";
    Observer::print();
}

void NewspaperObserver::printMeteo() const {
    std::cout << "Newspaper ";
    Observer::print();
}
