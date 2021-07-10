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

#include "Duelist.hpp"
#include "StringOperations.hpp"

Duelist::Duelist() {
    this->name = new char[1];
    this->name[0] = '\0';
}

Duelist::Duelist(const char *name, Deck &deck) {
    int nameLength = stringLength(name);
    this->name = new char[nameLength + 1];
    stringCopy(name, this->name);
    this->deck = deck;
}

Duelist::Duelist(const Duelist &duelist) {
    delete[] this->name;
    this->name = new char[stringLength(duelist.name) + 1];
    stringCopy(duelist.name, this->name);
    this->deck = duelist.deck;
}

Duelist::~Duelist() {
    delete[] this->name;
}

void Duelist::addMagicCardInDeck(MagicCard magicCard) {
    this->deck.addMagicCard(magicCard);
}

void Duelist::addMonsterCardInDeck(MonsterCard monsterCard) {
    this->deck.addMonsterCard(monsterCard);
}

void Duelist::changeMagicCardInDeck(unsigned int index, MagicCard magicCard) {
    this->deck.changeMagicCard(index, magicCard);
}

void Duelist::changeMonsterCardInDeck(unsigned int index, MonsterCard monsterCard) {
    this->deck.changeMonsterCard(index, monsterCard);
}

void Duelist::printDeck() const {
    this->deck.printDeck();
}
