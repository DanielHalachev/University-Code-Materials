/**
* Solution to homework assignment 3
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Daniel Halachev
* @idnumber 62547
* @task 1
* @compiler GCC
*/

#include "Card.hpp"

Card::Card(const std::string &name, const std::string &effect) {
    this->name = name;
    this->effect = effect;
}

std::string Card::getName() const {
    return this->name;
}

std::string Card::getEffect() const {
    return this->effect;
}

//void Card::setName(std::string &name) {
//    this->name = name;
//}

//void Card::setEffect(std::string &effect) {
//    this->effect = effect;
//}

