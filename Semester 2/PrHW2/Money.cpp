/**
* Solution to homework assignment 2
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Daniel Halachev
* @idnumber 62547
* @task 1
* @compiler GCC
*/

#include "Money.hpp"
#include "iostream"

Money::Money() {
    this->quantity = 0;
}

Money::Money(const unsigned int &moneyInSilver) {
    this->quantity = moneyInSilver;
}

unsigned int Money::getQuantity() const {
    return this->quantity;
}

unsigned int Money::getSilver() const {
    return this->quantity % 100;
}

unsigned int Money::getGold() const {
    return this->quantity / 100;
}

void Money::setMoney(const unsigned int &newQuantity) {
    this->quantity = newQuantity;
}

void Money::addGold(const unsigned int &gold) {
    this->quantity = this->quantity + gold * 100;
}

void Money::addSilver(const unsigned int &silver) {
    this->quantity = this->quantity + silver;
}

bool Money::subtractGold(unsigned int &gold) {
    if (this->quantity < gold * 100) {
        return false;
    }
    this->quantity = this->quantity - gold * 100;
    return true;
}

bool Money::subtractSilver(unsigned int &silver) {
    if (this->quantity < silver) {
        return false;
    }
    this->quantity = this->quantity - silver;
    return true;
}

std::ostream &operator<<(std::ostream &out, const Money &money) {
    out << "\nMoney:\n" << "Gold: " << money.getGold() << "\nSilver: " << money.getSilver() << "\nQuantity: "
        << money.getQuantity() << "\n";

    return out;
}
