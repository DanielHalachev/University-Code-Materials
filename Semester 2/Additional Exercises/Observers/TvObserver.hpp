//
// Created by User on 3.6.2021 г..
//

#ifndef EXERCISES_TVOBSERVER_HPP
#define EXERCISES_TVOBSERVER_HPP


#include "Observer.hpp"

class TVObserver : public Observer {
public:
    TVObserver(const std::string &name = "", const std::string &city = "", const double &temperature = 0);

    void update(const std::string &city, const double &newTemperature) override;
    void printMeteo() const override;
};


#endif //EXERCISES_TVOBSERVER_HPP
