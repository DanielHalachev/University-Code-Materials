//
// Created by User on 14.6.2021 г..
//

#ifndef EXERCISES_DRINK_HPP
#define EXERCISES_DRINK_HPP


#include "StoreProduct.hpp"

class Drink : public StoreProduct {
public:
    explicit Drink(const std::string &name = "", const std::string &code = "", const double &price = 0,
                   const double &alcoholPercentage = 0);

    Drink *clone() const override;

    void print(std::ostream &out) const override;

private:
    double alcoholPercentage;
};


#endif //EXERCISES_DRINK_HPP
