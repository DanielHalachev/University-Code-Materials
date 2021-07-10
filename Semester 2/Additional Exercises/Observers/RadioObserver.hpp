//
// Created by User on 3.6.2021 г..
//

#ifndef EXERCISES_RADIOOBSERVER_HPP
#define EXERCISES_RADIOOBSERVER_HPP


#include <string>
#include "Observer.hpp"

class RadioObserver : public Observer {
public:
    RadioObserver(const std::string &name = "", const std::string &city = "", const double &temperature = 0);

    void update(const std::string &city, const double &newTemperature) override;

    void printMeteo() const override;
};


#endif //EXERCISES_RADIOOBSERVER_HPP
