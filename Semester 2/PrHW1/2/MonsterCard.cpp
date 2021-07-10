/**
* Solution to homework assignment 1
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Daniel Halachev
* @idnumber 62547
* @task 2
* @compiler GCC
*/

#include "MonsterCard.hpp"
#include "StringOperations.hpp"

MonsterCard::MonsterCard() {
    this->name[0] = '\0';
    this->attackPoints = 0;
    this->defensePoints = 0;
    this->isEmpty = true;
}

MonsterCard::MonsterCard(const char *name, unsigned int attack, unsigned int defense) {
    stringCopy(name, this->name);
    this->attackPoints = attack;
    this->defensePoints = defense;
    this->isEmpty = false;
}

bool MonsterCard::cardIsEmpty() const {
    return this->isEmpty;
}

const char *MonsterCard::getName() const {
    return this->name;
}

unsigned int MonsterCard::getAttack() const {
    return this->attackPoints;
}

unsigned int MonsterCard::getDefense() const {
    return this->defensePoints;
}