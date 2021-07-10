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

#include <string>
#include "MonsterCard.hpp"


MonsterCard::MonsterCard() : Card("", "") {
    this->attackPoints = 0;
    this->defensePoints = 0;
}

MonsterCard::MonsterCard(const std::string &name, const std::string &effect, const unsigned int &attack,
                         const unsigned int &defense)
        : Card(name, effect) {

    this->attackPoints = attack;
    this->defensePoints = defense;
}

unsigned int MonsterCard::getAttack() const {
    return this->attackPoints;
}

unsigned int MonsterCard::getDefense() const {
    return this->defensePoints;
}

std::ostream &operator<<(std::ostream &out, const MonsterCard &monsterCard) {
    char delimChar = '|';
    out << monsterCard.name << delimChar << monsterCard.effect << delimChar << monsterCard.attackPoints << delimChar
        << monsterCard.defensePoints;
    return out;
}

std::istream &operator>>(std::istream &in, MonsterCard &monsterCard) {
    char delimChar = '|';
    // get and set the name
    getline(in, monsterCard.name, delimChar);
    // get and set the effect
    getline(in, monsterCard.effect, delimChar);
    // get and set the attack and defence
    in >> monsterCard.attackPoints >> delimChar
       >> monsterCard.defensePoints;
    return in;
}

//void MonsterCard::setAttack(const unsigned int &attack) {
//    this->attackPoints = attack;
//}

//void MonsterCard::setDefence(const unsigned int &defense) {
//    this->defensePoints = defense;
//}

