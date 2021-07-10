//
// Created by User on 22.3.2021 г..
//
#include <cstring>
#include <iostream>
#include "VendingMachine.hpp"

VendingMachine::VendingMachine() {
    this->storage = nullptr;
    this->income = 0.0;
    this->totalDrinks = 0;
}

VendingMachine::VendingMachine(const VendingMachine &from) {
    this->storage = new Drink *[from.totalDrinks];
    for (int i = 0; i < from.totalDrinks; i++) {
        this->storage[i] = new Drink(*from.storage[i]);
    }
    this->totalDrinks = from.totalDrinks;
    this->income = from.income;
}

VendingMachine::~VendingMachine() {
    this->DeleteMemory();
}

VendingMachine &VendingMachine::operator=(const VendingMachine &from) {
    if (this != &from) {
        // delete old memory
        this->DeleteMemory();
        // assign new data
        this->storage = new Drink *[from.totalDrinks];
        for (int i = 0; i < from.totalDrinks; i++) {
            this->storage[i] = new Drink(*from.storage[i]);
        }
        this->totalDrinks = from.totalDrinks;
        this->income = from.income;
    }
    return *this;
}

bool VendingMachine::add_drink(const Drink &drink) {
    // in case the drink already exists, we can't add it
    if (this->drinkExists(drink.get_name()) != -1) {
        return false;
    }
    // in case it doesn't exist already, proceed
    // create array to store the old drinks and the new one
    Drink **newArray = new Drink *[this->totalDrinks + 1];
    for (int i = 0; i < this->totalDrinks; i++) {
        newArray[i] = new Drink(*this->storage[i]);
    }
    newArray[totalDrinks] = new Drink(drink);
    // delete the memory before assigning it a new value
    this->DeleteMemory();
    // don't forget to increase the number of drinks
    this->totalDrinks++;
    this->storage = newArray;
    // everything is alright, show it
    return true;
}

int VendingMachine::buy_drink(const char *drink_name, const double money) {
    // get the index of the drink if it exists
    int index = this->drinkExists(drink_name);
    std::cout<<index<<std::endl;
    // in case the drink doesn't exist, terminate the operation
    if (index == -1) {
        return 2;
    }
    // in case the drink exists, the machine gets you money no matter how
    this->income = this->income + money;
    // however, if the money is not enough, no drink for you. You will be thirsty
    if (money < this->storage[index]->get_price()) {
        return 1;
    }
    // in case the drink exists and you've paid enough,
    // get the drink and remove it from storage
    // all drinks before the bought one remain the same
    Drink **newArray = new Drink *[this->totalDrinks - 1];
    for (int i = 0; i < index; i++) {
        newArray[i] = new Drink(*this->storage[i]);
    }
    // move all drinks after the bought one one place to the left to fill the "hole"
    for (int i = index; i < this->totalDrinks - 1; i++) {
        newArray[i] = new Drink(*this->storage[i + 1]);
    }
    // delete the old memory before assigning it any new values
    this->DeleteMemory();
    this->totalDrinks--;
    this->storage = newArray;
    return 0;
}

void VendingMachine::DeleteMemory() const {
    for (int i = 0; i < totalDrinks; i++) {
        delete storage[i];
    }
    delete[] storage;
}

double VendingMachine::get_income() const {
    return this->income;
}

int VendingMachine::drinkExists(const char *drinkName) const {
    // search through all drinks
    for (int i = 0; i < this->totalDrinks; i++) {
        // in case of finding a match, stop further searching
        if (strcmp(this->storage[i]->get_name(), drinkName)==0) {
            // return the index of the found drink
            return i;
        }
    }
    // return an invalid index in case the drink doesn't exist
    return -1;
}