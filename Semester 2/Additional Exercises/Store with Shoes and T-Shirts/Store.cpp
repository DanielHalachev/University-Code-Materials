//
// Created by User on 8.6.2021 г..
//

#include "Store.hpp"

void Store::addProduct(StoreItem *item) {
    this->items.push_back(item->clone());
}

bool Store::removeProduct(const unsigned int &index) {
    if (index > this->items.size() - 1) {
        return false;
    }
    this->items.erase(this->items.begin() + index);
    return true;
}

bool Store::changePrice(const unsigned int &index, const double &newPrice) {
    if (index > this->items.size() - 1) {
        return false;
    }
    this->items[index]->setPrice(newPrice);
    return true;
}

bool Store::changeName(const unsigned int &index, const std::string &newName) {
    if (index > this->items.size() - 1) {
        return false;
    }
    this->items[index]->setName(newName);
    return true;
}

void Store::print() const {
    for (auto item:this->items) {
        item->print();
    }
}

Store::Store(const Store &other) {
    for (auto item:other.items) {
        this->items.push_back(item->clone());
    }
}

Store &Store::operator=(const Store &other) {
    if (this != &other) {
        for (auto item:other.items) {
            this->items.push_back(item->clone());
        }
    }
    return *this;
}

Store::~Store() {
    for (auto item:this->items) {
        delete item;
    }
}
