//
// Created by User on 29.5.2021 г..
//

#ifndef EXERCISES_BEER_HPP
#define EXERCISES_BEER_HPP


#include "Drink.hpp"

enum BeerType {
    LIGHT_LAGER, DARK_LAGER, PALE_ALE, IPA, BOK, WEISS, LIVE, OTHER
};

class Beer : public virtual Drink {
public:
    Beer(const std::string &brand, const double &alcoholPercentage = 0, const double &quantity = 0,
         const bool &isCraft = true, const BeerType &type = OTHER);

private:
    bool isCraft;
    BeerType type;
};


#endif //EXERCISES_BEER_HPP
