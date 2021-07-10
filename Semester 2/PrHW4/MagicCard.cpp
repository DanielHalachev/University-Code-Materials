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
#include "MagicCard.hpp"

MagicCard::MagicCard() : Card("", "", 0) {
    this->type = NONE;
}

MagicCard::MagicCard(const std::string &name, const std::string &effect, const unsigned int &rarity, const Type &type)
        : Card(name, effect, rarity) {
    if (type == NONE) {
        this->type = TRAP; //random type different than NONE
    } else {
        this->type = type;
    }
}

MagicCard *MagicCard::clone() const {
    return new MagicCard(*this);
}

MagicCard::Type MagicCard::getType() const {
    return this->type;
}

std::istream &MagicCard::read(std::istream &in) {
    char delimChar = '|';
    // create a string to store the enum value
    std::string enumValue;
    // get and set the name
    getline(in, this->name, delimChar);
    // get and set the effect
    getline(in, this->effect, delimChar);
    // get rarity
    in >> this->rarity >> delimChar;
    // get the type
    getline(in, enumValue, '\n');
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

std::ostream &MagicCard::print(std::ostream &out) const {
    char delimChar = '|';
    std::string enumValue;
    // create a string according to the enum value
    if (this->type == MagicCard::TRAP) {
        enumValue = "TRAP";
    } else if (this->type == MagicCard::BUFF) {
        enumValue = "BUFF";
    } else if (this->type == MagicCard::SPELL) {
        enumValue = "SPELL";
    } else {
        enumValue = "NONE";
    }
    out << this->name << delimChar << this->effect << delimChar << this->rarity << delimChar << enumValue;
    return out;
}

//void MagicCard::setType(const MagicCard::Type &type) {
//    this->type = type;
//}



