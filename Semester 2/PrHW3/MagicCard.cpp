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
#include "MagicCard.hpp"

MagicCard::MagicCard() : Card("", "") {
    this->type = NONE;
}

MagicCard::MagicCard(const std::string &name, const std::string &effect, const Type &type) : Card(name, effect) {
    if (type == NONE) {
        this->type = TRAP; //random type different than NONE
    } else {
        this->type = type;
    }
}

MagicCard::Type MagicCard::getType() const {
    return this->type;
}

std::ostream &operator<<(std::ostream &out, const MagicCard &magicCard) {
    char delimChar = '|';
    std::string enumValue;
    // create a string according to the enum value
    if (magicCard.type == MagicCard::TRAP) {
        enumValue = "TRAP";
    } else if (magicCard.type == MagicCard::BUFF) {
        enumValue = "BUFF";
    } else if (magicCard.type == MagicCard::SPELL) {
        enumValue = "SPELL";
    } else {
        enumValue = "NONE";
    }
    out << magicCard.name << delimChar << magicCard.effect << delimChar << enumValue;
    return out;
}

std::istream &operator>>(std::istream &in, MagicCard &magicCard) {
    char delimChar = '|';
    // create a string to store the enum value
    std::string enumValue;
    // get and set the name
    getline(in, magicCard.name, delimChar);
    // get and set the effect
    getline(in, magicCard.effect, delimChar);
    // get the type
    getline(in, enumValue, '\n');
    // set the type
    if (enumValue == "TRAP") {
        magicCard.type = MagicCard::TRAP;
    } else if (enumValue == "BUFF") {
        magicCard.type = MagicCard::BUFF;
    } else if (enumValue == "SPELL") {
        magicCard.type = MagicCard::SPELL;
    } else {
        magicCard.type = MagicCard::NONE;
    }
    return in;
}

//void MagicCard::setType(const MagicCard::Type &type) {
//    this->type = type;
//}



