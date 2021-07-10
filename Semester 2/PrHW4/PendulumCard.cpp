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

#include "PendulumCard.hpp"

PendulumCard::PendulumCard() : MonsterCard(), MagicCard() {
    this->scale = MIN_SCALE;
}

PendulumCard::PendulumCard(const std::string &name, const std::string &effect, const unsigned int &rarity,
                           const unsigned int &attack,
                           const unsigned int &defense, const Type &type, const unsigned short &scale)
        : Card(name, effect, rarity), MagicCard(name, effect, rarity, type),
          MonsterCard(name, effect, rarity, attack, defense) {
    // check if the scale is correct and make adjustments if needed
    if (scale < MIN_SCALE) {
        this->scale = MIN_SCALE;
    } else if (scale > MAX_SCALE) {
        this->scale = scale % MAX_SCALE;
    } else {
        this->scale = scale;
    }
}

PendulumCard *PendulumCard::clone() const {
    return new PendulumCard(*this);
}

unsigned short PendulumCard::getScale() const {
    return this->scale;
}

std::istream &PendulumCard::read(std::istream &in) {
    char delimChar = '|';
    // create a string to store type
    std::string enumValue;
    // get and set the name
    getline(in, this->name, delimChar);
    // get and set the effect
    getline(in, this->effect, delimChar);
    // get and set the attack, defence and scale; get the type
    in >> this->rarity >> delimChar >> this->attackPoints >> delimChar
       >> this->defensePoints >> delimChar >> this->scale >> delimChar >> enumValue;
    // set the type
    if (enumValue == "TRAP") {
        this->type = MagicCard::TRAP;
    } else if (enumValue == "BUFF") {
        this->type = MagicCard::BUFF;
    } else if (enumValue == "SPELL") {
        this->type = MagicCard::SPELL;
    } else {
        this->type = MagicCard::NONE;
    }
    return in;
}

std::ostream &PendulumCard::print(std::ostream &out) const {
    char delimChar = '|';
    // create a string to store the type
    std::string enumValue;
    // set it correctly
    if (this->type == MagicCard::TRAP) {
        enumValue = "TRAP";
    } else if (this->type == MagicCard::BUFF) {
        enumValue = "BUFF";
    } else if (this->type == MagicCard::SPELL) {
        enumValue = "SPELL";
    } else {
        enumValue = "NONE";
    }
    // print print
    out << this->name << delimChar << this->effect << delimChar << this->rarity << delimChar << this->attackPoints
        << delimChar << this->defensePoints << delimChar << this->scale << delimChar << enumValue;
    return out;
}

//bool PendulumCard::setScale(const unsigned int &newScale) {
//    if (newScale < MIN_SCALE || newScale > MAX_SCALE) {
//        return false;
//    }
//    this->scale = newScale;
//    return true;
//}
