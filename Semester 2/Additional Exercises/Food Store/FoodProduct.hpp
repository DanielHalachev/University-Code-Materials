//
// Created by User on 14.6.2021 г..
//

#ifndef EXERCISES_FOODPRODUCT_HPP
#define EXERCISES_FOODPRODUCT_HPP


#include "StoreProduct.hpp"

class FoodProduct : public StoreProduct {
public:
    explicit FoodProduct(const std::string &name = "", const std::string &code = "", const double &price = 0,
                         const unsigned int &calories = 0);

    FoodProduct *clone() const override;

    void print(std::ostream &out) const override;

private:
    unsigned int calories;
};

#endif //EXERCISES_FOODPRODUCT_HPP
