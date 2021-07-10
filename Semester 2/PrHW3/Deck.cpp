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

#include "Deck.hpp"
#include "iostream"

Deck::Deck(const std::string &name) {
    this->name = name;
}

Deck::Deck(const Deck &deck) {
    // copy the name
    this->name = deck.name;
    // copy the monster cards
    for (const MonsterCard &card: deck.monsterCards) {
        this->monsterCards.push_back(card);
    }
    // copy the magic cards
    for (const MagicCard &card: deck.magicCards) {
        this->magicCards.push_back(card);
    }
    // copy the pendulum cards
    for (const PendulumCard &card: deck.pendulumCards) {
        this->pendulumCards.push_back(card);
    }
}

Deck &Deck::operator=(const Deck &other) {
    if (this != &other) {
        // copy the name
        this->name = other.name;
        // copy the monster cards
        for (const MonsterCard &card: other.monsterCards) {
            this->monsterCards.push_back(card);
        }
        //copy the magic cards
        for (const MagicCard &card: other.magicCards) {
            this->magicCards.push_back(card);
        }
        // copy the pendulum cards
        for (const PendulumCard &card: other.pendulumCards) {
            this->pendulumCards.push_back(card);
        }
    }
    return *this;
}

std::string Deck::getName() const {
    return this->name;
}

unsigned int Deck::getMonsterCardCount() const {
    return this->monsterCards.size();
}

unsigned int Deck::getMagicCardCount() const {
    return this->magicCards.size();
}

unsigned int Deck::getPendulumCardCount() const {
    return this->pendulumCards.size();
}

void Deck::addMagicCard(const MagicCard &magicCard) {
    this->magicCards.push_back(magicCard);
}

void Deck::addMonsterCard(const MonsterCard &monsterCard) {
    this->monsterCards.push_back(monsterCard);
}

void Deck::addPendulumCard(const PendulumCard &pendulumCard) {
    this->pendulumCards.push_back(pendulumCard);
}

bool Deck::changeMagicCard(const unsigned int &index, const MagicCard &magicCard) {
    // check if the index is valid before execution
    if (index < 0 || index > this->magicCards.size() - 1) {
        return false;
    }
    // if it's correct, change the card
    this->magicCards[index] = magicCard;
    return true;
}

bool Deck::changeMonsterCard(const unsigned int &index, const MonsterCard &monsterCard) {
    // check if the index is valid before execution
    if (index < 0 || index > this->monsterCards.size() - 1) {
        return false;
    }
    // if it's correct, change the card
    this->monsterCards[index] = monsterCard;
    return true;
}

bool Deck::changePendulumCard(const unsigned int &index, const PendulumCard &pendulumCard) {
    // check if the index is valid before execution
    if (index < 0 || index > this->pendulumCards.size() - 1) {
        return false;
    }
    // if it's correct, change the card
    this->pendulumCards[index] = pendulumCard;
    return true;
}

void Deck::clearDeck() {
    this->monsterCards.clear();
    this->magicCards.clear();
    this->pendulumCards.clear();
}

std::ostream &operator<<(std::ostream &out, const Deck &deck) {
    out << deck.name << "|" << deck.getMonsterCardCount() << "|" << deck.getMagicCardCount() << "|"
        << deck.getPendulumCardCount() << "\n";
    // print all the monster cards
    for (const MonsterCard &card: deck.monsterCards) {
        out << card << "\n";
    }
    // print all the magic cards
    for (const MagicCard &card: deck.magicCards) {
        out << card << "\n";
    }
    // print all the pendulum cards
    for (const PendulumCard &card: deck.pendulumCards) {
        out << card << "\n";
    }
    return out;
}

std::istream &operator>>(std::istream &in, Deck &deck) {
    char delimChar = '|';
    // temporary variables to store the number of cards
    unsigned int monsterCount = 0, magicCount = 0, pendulumCount = 0;
    // temporary variables to store the corresponding cards before storage
    MonsterCard monsterTemp;
    MagicCard magicTemp;
    PendulumCard pendulumTemp;
    // get the name
    getline(in, deck.name, delimChar);
    // get the card count
    in >> monsterCount >> delimChar >> magicCount >> delimChar >> pendulumCount;
    // ignore the '\n' symbol which will cause a wrong name of the first card
    in.ignore();
    // read all the monster cards
    for (int i = 0; i < monsterCount; i++) {
        in >> monsterTemp;
        if (in.get() == '\n') {
            deck.monsterCards.push_back(monsterTemp);
        }
    }
    // read all the magic cards
    for (int i = 0; i < magicCount; i++) {
        in >> magicTemp;
        deck.magicCards.push_back(magicTemp);
    }
    // read all the pendulum cards
    for (int i = 0; i < pendulumCount; i++) {
        in >> pendulumTemp;
        deck.pendulumCards.push_back(pendulumTemp);
    }
    return in;
}

//void Deck::setName(const std::string &newName) {
//    this->name = newName;
//}

