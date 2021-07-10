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

#include "PendulumCard.hpp"

PendulumCard::PendulumCard() : MonsterCard(), MagicCard() {
    this->scale = MIN_SCALE;
}

PendulumCard::PendulumCard(const std::string &name, const std::string &effect, const unsigned int &attack,
                           const unsigned int &defense, const Type &type, const unsigned short &scale)
        : Card(name, effect), MagicCard(name, effect, type), MonsterCard(name, effect, attack, defense) {
    // check if the scale is correct and make adjustments if needed
    if (scale < MIN_SCALE) {
        this->scale = MIN_SCALE;
    } else if (scale > MAX_SCALE) {
        this->scale = scale % MAX_SCALE;
    } else {
        this->scale = scale;
    }
}

unsigned short PendulumCard::getScale() const {
    return this->scale;
}

std::ostream &operator<<(std::ostream &out, const PendulumCard &pendulumCard) {
    char delimChar = '|';
    // create a string to store the type
    std::string enumValue;
    // set it correctly
    if (pendulumCard.type == MagicCard::TRAP) {
        enumValue = "TRAP";
    } else if (pendulumCard.type == MagicCard::BUFF) {
        enumValue = "BUFF";
    } else if (pendulumCard.type == MagicCard::SPELL) {
        enumValue = "SPELL";
    } else {
        enumValue = "NONE";
    }
    // print out
    out << pendulumCard.name << delimChar << pendulumCard.effect << delimChar << pendulumCard.attackPoints << delimChar
        << pendulumCard.defensePoints << delimChar << pendulumCard.scale << delimChar << enumValue;
    return out;
}

std::istream &operator>>(std::istream &in, PendulumCard &pendulumCard) {
    char delimChar = '|';
    // create a string to store type
    std::string enumValue;
    // get and set the name
    getline(in, pendulumCard.name, delimChar);
    // get and set the effect
    getline(in, pendulumCard.effect, delimChar);
    // get and set the attack, defence and scale; get the type
    in >> pendulumCard.attackPoints >> delimChar
       >> pendulumCard.defensePoints >> delimChar >> pendulumCard.scale >> delimChar >> enumValue;
    // set the type
    if (enumValue == "TRAP") {
        pendulumCard.type = MagicCard::TRAP;
    } else if (enumValue == "BUFF") {
        pendulumCard.type = MagicCard::BUFF;
    } else if (enumValue == "SPELL") {
        pendulumCard.type = MagicCard::SPELL;
    } else {
        pendulumCard.type = MagicCard::NONE;
    }
    return in;
}

//bool PendulumCard::setScale(const unsigned int &newScale) {
//    if (newScale < MIN_SCALE || newScale > MAX_SCALE) {
//        return false;
//    }
//    this->scale = newScale;
//    return true;
//}
