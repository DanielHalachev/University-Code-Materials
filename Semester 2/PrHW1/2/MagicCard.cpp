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

#include "MagicCard.hpp"
#include "StringOperations.hpp"

MagicCard::MagicCard() {
    this->name[0] = '\0';
    this->effect[0] = '\0';
    this->type = none;
}

MagicCard::MagicCard(const char *name, const char *effect, Type type) {
    stringCopy(name, this->name);
    stringCopy(effect, this->effect);
    if (type == none) {
        type = trap; //random type different than none
    }
    this->type = type;
}

const char *MagicCard::getName() const {
    return this->name;
}

const char *MagicCard::getEffect() const {
    return this->effect;
}

MagicCard::Type MagicCard::getType() const {
    return this->type;
}