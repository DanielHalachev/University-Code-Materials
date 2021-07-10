//
// Created by User on 8.6.2021 г..
//

#ifndef EXERCISES_STORE_HPP
#define EXERCISES_STORE_HPP


#include <vector>
#include "StoreItem.hpp"

class Store {
public:
    Store() = default;

    Store(const Store &other);

    Store &operator=(const Store &other);

    ~Store();

    void addProduct(StoreItem *item);

    bool removeProduct(const unsigned int &index);

    bool changePrice(const unsigned int &index, const double &newPrice);

    bool changeName(const unsigned int &index, const std::string &newName);

    void print() const;

private:
    std::string name;
    std::vector<StoreItem *> items;
};


#endif //EXERCISES_STORE_HPP
