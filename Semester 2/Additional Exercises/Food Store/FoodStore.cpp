//
// Created by User on 14.6.2021 г..
//

#include "FoodStore.hpp"

FoodStore::FoodStore(const FoodStore &other) {
    for (auto item:other.items) {
        this->items.push_back(item->clone());
    }
}

FoodStore &FoodStore::operator=(const FoodStore &other) {
    if (this != &other) {
        for (auto item:this->items) {
            delete item;
        }
        for (auto item:other.items) {
            this->items.push_back(item->clone());
        }
    }
    return *this;
}

FoodStore::~FoodStore() {
    for (auto item:this->items) {
        delete item;
    }
}

void FoodStore::addProduct(const StoreProduct *const &product) {
    if (product != nullptr) {
        this->items.push_back(product->clone());
    }
}

bool FoodStore::removeProduct(const std::string &code) {
    for (unsigned int i = 0; i < this->items.size(); i++) {
        if (this->items[i]->getCode() == code) {
            this->items.erase(this->items.begin() + i);
            return true;
        }
    }
    return false;
}

void FoodStore::printByPrice(const double &price) const {
    for (auto item:this->items) {
        if (item->getPrice() < price) {
            std::cout << item;
        }
    }
}

StoreProduct *FoodStore::find(const std::string &code) const {
    for (auto item : this->items) {
        if (item->getCode() == code) {
            return item;
        }
    }
    return nullptr;
}
