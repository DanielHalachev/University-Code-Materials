//
// Created by User on 3.6.2021 г..
//

#ifndef EXERCISES_NEWSPAPEROBSERVER_HPP
#define EXERCISES_NEWSPAPEROBSERVER_HPP


#include <string>
#include "Observer.hpp"

class NewspaperObserver : public Observer {
public:
    NewspaperObserver(const std::string &name = "", const std::string &city = "", const double &temperature = 0);

    void update(const std::string &city, const double &newTemperature) override;
    void printMeteo() const override;
};


#endif //EXERCISES_NEWSPAPEROBSERVER_HPP
