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

#include <string>
#include "MonsterCard.hpp"


MonsterCard::MonsterCard() : Card("", "", 0) {
    this->attackPoints = 0;
    this->defensePoints = 0;
}

MonsterCard::MonsterCard(const std::string &name, const std::string &effect, const unsigned int &rarity,
                         const unsigned int &attack,
                         const unsigned int &defense)
        : Card(name, effect, rarity) {

    this->attackPoints = attack;
    this->defensePoints = defense;
}

MonsterCard *MonsterCard::clone() const {
    return new MonsterCard(*this);
}

unsigned int MonsterCard::getAttack() const {
    return this->attackPoints;
}

unsigned int MonsterCard::getDefense() const {
    return this->defensePoints;
}

std::istream &MonsterCard::read(std::istream &in) {
    char delimChar = '|';
    // get and set the name
    getline(in, this->name, delimChar);
    // get and set the effect
    getline(in, this->effect, delimChar);
    // get and set the attack and defence
    in >> this->rarity >> delimChar >> this->attackPoints >> delimChar >> this->defensePoints;
    return in;
}

std::ostream &MonsterCard::print(std::ostream &out) const {
    char delimChar = '|';
    out << this->name << delimChar << this->effect << delimChar << this->rarity << delimChar << this->attackPoints
        << delimChar << this->defensePoints;
    return out;
}

//void MonsterCard::setAttack(const unsigned int &attack) {
//    this->attackPoints = attack;
//}

//void MonsterCard::setDefence(const unsigned int &defense) {
//    this->defensePoints = defense;
//}

