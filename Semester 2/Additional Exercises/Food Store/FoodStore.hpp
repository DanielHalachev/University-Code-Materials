//
// Created by User on 14.6.2021 г..
//

#ifndef EXERCISES_FOODSTORE_HPP
#define EXERCISES_FOODSTORE_HPP


#include <vector>
#include "StoreProduct.hpp"

class FoodStore {
public:
    FoodStore() = default;

    FoodStore(const FoodStore &other);

    FoodStore &operator=(const FoodStore &other);

    ~FoodStore();

    void addProduct(const StoreProduct *const &product);

    bool removeProduct(const std::string &code);

    void printByPrice(const double &price) const;

    StoreProduct *find(const std::string &code) const;

private:
    std::vector<StoreProduct *> items;
};


#endif //EXERCISES_FOODSTORE_HPP
