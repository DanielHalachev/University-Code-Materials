/**
* Solution to homework assignment 4
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

Card::Card(const std::string &name, const std::string &effect, const unsigned int &rarity) {
    this->name = name;
    this->effect = effect;
    this->rarity = rarity;
}

std::string Card::getName() const {
    return this->name;
}

std::string Card::getEffect() const {
    return this->effect;
}

unsigned int Card::getRarity() const {
    return this->rarity;
}

bool Card::operator<(const Card &other) const {
    return (this->rarity < other.rarity);
}

bool Card::operator>(const Card &other) const {
    return (this->rarity > other.rarity);
}

std::ostream &operator<<(std::ostream &out, const Card &card) {
    return card.print(out);
}

std::istream &operator>>(std::istream &in, Card &card) {
    return card.read(in);
}

//void Card::setName(std::string &name) {
//    this->name = name;
//}

//void Card::setEffect(std::string &effect) {
//    this->effect = effect;
//}

//void Card::setRarity(const unsigned int newRarity) {
//    this->rarity = newRarity;
//}
