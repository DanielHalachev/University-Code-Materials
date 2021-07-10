//
// Created by User on 29.5.2021 г..
//

#ifndef EXERCISES_COKE_HPP
#define EXERCISES_COKE_HPP

#include <string>
#include "SoftDrink.hpp"

enum CokeType {
    CLASSIC, LIGHT, ZERO
};

class Coke : public SoftDrink {
public:
    Coke(const double &quantity = 0, const CokeType &type = CLASSIC);

    CokeType getType() const;

    std::string toString() const override;

private:
    CokeType type;
};


#endif //EXERCISES_COKE_HPP
