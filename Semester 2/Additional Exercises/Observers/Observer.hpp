//
// Created by User on 3.6.2021 г..
//

#ifndef EXERCISES_OBSERVER_HPP
#define EXERCISES_OBSERVER_HPP


#include <string>

class Observer {
public:
    Observer(const std::string &name, const std::string &city, const double &temperature);

    virtual void update(const std::string &city, const double &newTemperature) = 0;

    virtual void printMeteo() const = 0;

    void print() const;

protected:
    std::string name;
    std::string city;
    double currentTemperature;
};


#endif //EXERCISES_OBSERVER_HPP
