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

#include <fstream>
#include "Duelist.hpp"

Duelist::Duelist(const std::string &name) {
    this->name = name;
    this->deck = Deck();
}

Duelist::Duelist(const std::string &name, const Deck &deck) {
    this->name = name;
    this->deck = deck;
}

Duelist::Duelist(const Duelist &duelist) {
    this->name = duelist.name;
    this->deck = duelist.deck;
}

void Duelist::addMagicCardInDeck(const MagicCard &magicCard) {
    this->deck.addMagicCard(magicCard);
}

void Duelist::addMonsterCardInDeck(const MonsterCard &monsterCard) {
    this->deck.addMonsterCard(monsterCard);
}

void Duelist::addPendulumCardInDeck(const PendulumCard &pendulumCard) {
    this->deck.addMonsterCard(pendulumCard);
}

void Duelist::changeMagicCardInDeck(const unsigned int &index, const MagicCard &magicCard) {
    this->deck.changeMagicCard(index, magicCard);
}

void Duelist::changeMonsterCardInDeck(const unsigned int &index, const MonsterCard &monsterCard) {
    this->deck.changeMonsterCard(index, monsterCard);
}

void Duelist::changePendulumCardInDeck(const unsigned int &index, const PendulumCard &pendulumCard) {
    this->deck.changeMonsterCard(index, pendulumCard);
}

Deck &Duelist::getDeck() {
    return (this->deck);
}

bool Duelist::writeInFile(const std::string &fileDirectory) {
    std::ofstream fileDialog;
    // open the file and delete all previous data in it before writing
    fileDialog.open(fileDirectory, std::ios::out);
    if (!fileDialog) {
        return false;
    }
    fileDialog << this->deck;
    // close
    fileDialog.close();
    return true;
}

bool Duelist::readFromFile(const std::string &FileDirectory) {
    std::ifstream fileDialog;
    fileDialog.open(FileDirectory);
    if (!fileDialog) {
        return false;
    }
    // if everything's alright, clear the previous data
    this->deck.clearDeck();
    fileDialog >> (this->deck);
    fileDialog.close();
    return true;
}
