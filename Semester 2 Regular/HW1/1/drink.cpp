//
// Created by User on 22.3.2021 г..
//
#include <cstring>
#include "drink.hpp"

Drink::Drink(const char *init_name, const int init_calories, const double &init_quantity, const double &init_price) {
    this->name = new char[strlen(init_name) + 1];
    strcpy(this->name, init_name);
    this->calories = init_calories;
    this->quantity = init_quantity;
    this->price = init_price;
}

Drink::Drink(const Drink &drink) {
    this->name = new char[strlen(drink.name) + 1];
    strcpy(this->name, drink.name);
    this->calories = drink.calories;
    this->quantity = drink.quantity;
    this->price = drink.price;
}

Drink::~Drink() {
    delete[] this->name;
}

Drink &Drink::operator=(const Drink &other) {
    if (this != &other) {
        delete[] this->name;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->calories = other.calories;
        this->quantity = other.quantity;
        this->price = other.price;
    }
    return *this;
}

const char *Drink::get_name() const {
    return this->name;
}

int Drink::get_calories() const {
    return this->calories;
}

double Drink::get_quantity() const {
    return this->quantity;
}

double Drink::get_price() const {
    return this->price;
}

void Drink::set_name(const char *new_name) {
    delete[] this->name;
    this->name = new char[strlen(new_name) + 1];
    strcpy(this->name, new_name);
}

bool Drink::operator==(const Drink &other) const {
    return strcmp(this->name, other.name) == 0;
}
