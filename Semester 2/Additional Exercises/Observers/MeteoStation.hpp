//
// Created by User on 3.6.2021 г..
//

#ifndef EXERCISES_METEOSTATION_HPP
#define EXERCISES_METEOSTATION_HPP


#include <string>
#include <vector>
#include "Observer.hpp"

class MeteoStation {
public:
    explicit MeteoStation(const std::string &city = "", const double &temperature = 0);

    ~MeteoStation() = delete;

    void setTemperature(const double &newTemperature);

    std::string getCity() const;

    double getTemperature() const;

    void registerObserver(Observer *observer);

    bool unregister(Observer *observer);

    void notify() const;

private:
    std::string city;
    double temperature{};
    std::vector<Observer *> observers;
};


#endif //EXERCISES_METEOSTATION_HPP
