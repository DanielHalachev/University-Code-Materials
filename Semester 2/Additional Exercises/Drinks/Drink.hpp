//
// Created by User on 29.5.2021 г..
//

#ifndef EXERCISES_DRINK_HPP
#define EXERCISES_DRINK_HPP


#include <string>

class Drink {
public:
    Drink(const std::string &brand = "", const double &alcoholPercentage = 0, const double &quantity = 0);

    std::string getBrand() const;

    double getPercentage() const;

    double getQuantity() const;

    void add(const double &quantity);

    void remove(const double &quantity);

    virtual std::string toString() const;

protected:
    std::string brand;
    double alcoholPercentage;
    double quantityInLitres;

};


#endif //EXERCISES_DRINK_HPP
