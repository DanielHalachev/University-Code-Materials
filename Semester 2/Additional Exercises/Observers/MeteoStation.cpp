//
// Created by User on 3.6.2021 г..
//

#include "MeteoStation.hpp"

MeteoStation::MeteoStation(const std::string &city, const double &temperature)
        : city(city), temperature(temperature) {
}

void MeteoStation::setTemperature(const double &newTemperature) {
    this->temperature = newTemperature;
    this->notify();
}

std::string MeteoStation::getCity() const {
    return this->city;
}

double MeteoStation::getTemperature() const {
    return this->temperature;
}

void MeteoStation::registerObserver(Observer *observer) {
    this->observers.push_back(observer);
}

bool MeteoStation::unregister(Observer *observer) {
    for (int i = 0; i < this->observers.size(); i++) {
        if (this->observers[i] == observer) {
            this->observers.erase(this->observers.begin() + i);
            return true;
        }
    }
    return false;
}

void MeteoStation::notify() const {
    for(auto observer:this->observers){
        observer->update(this->city, this->temperature);
    }
}
