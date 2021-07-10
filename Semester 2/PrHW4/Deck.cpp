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
// the following two are used for sorting
#include <algorithm>
#include <random>
#include "Deck.hpp"
#include "iostream"

Deck::Deck(const std::string &name) {
    this->name = name;
    this->monsterCardsCount = 0;
    this->magicCardsCount = 0;
    this->pendulumCardsCount = 0;
}

Deck::Deck(const Deck &deck) {
    // copy the name and the number of cards
    this->name = deck.name;
    this->monsterCardsCount = deck.monsterCardsCount;
    this->magicCardsCount = deck.magicCardsCount;
    this->pendulumCardsCount = deck.pendulumCardsCount;
    // copy the cards themselves
    for (Card *card: deck.cards) {
        this->cards.push_back(card->clone());
    }
}

Deck &Deck::operator=(const Deck &other) {
    if (this != &other) {
        // copy the name and number of cards
        this->clearDeck();
        this->name = other.name;
        this->magicCardsCount = other.magicCardsCount;
        this->monsterCardsCount = other.monsterCardsCount;
        this->pendulumCardsCount = other.pendulumCardsCount;
        // copy the cards
        for (Card *card: other.cards) {
            this->cards.push_back(card->clone());
        }
    }
    return *this;
}

Deck::~Deck() {
    this->clearDeck();
}

void Deck::setName(const std::string &newName) {
    this->name = newName;
}

std::string Deck::getName() const {
    return this->name;
}

unsigned int Deck::getMonsterCardCount() const {
    return this->monsterCardsCount;
}

unsigned int Deck::getMagicCardCount() const {
    return this->magicCardsCount;
}

unsigned int Deck::getPendulumCardCount() const {
    return this->pendulumCardsCount;
}

unsigned int Deck::getCardCount() const {
    return this->cards.size();
}

Card &Deck::getCard(const unsigned int &index) const {
    return *this->cards.at(index);
}

void Deck::addCard(Card *card) {
    if (card == nullptr) {
        return;
    }
    unsigned short type = getCardType(card);
    switch (type) {
        case PENDULUM_CARD_PRIORITY:
            this->pendulumCardsCount++;
            break;
        case MAGIC_CARD_PRIORITY:
            this->magicCardsCount++;
            break;
        case MONSTER_CARD_PRIORITY:
            this->monsterCardsCount++;
            break;
    }
    this->cards.push_back(card->clone());
}

bool Deck::changeCard(const unsigned int &index, Card *card) {
    // check if the index is valid before execution
    if (index > this->cards.size() - 1 || card == nullptr) {
        return false;
    }
    // check if the types of old and new cards are the same
    unsigned short type1 = getCardType(this->cards[index]);
    unsigned short type2 = getCardType(card);
    if (type1 != type2) {
        return false;
    }
    // if everything's correct, change the card
    delete this->cards[index];
    this->cards[index] = card->clone();
    return true;
}

void Deck::shuffle() {
    // ensure that the shuffling is different every time
    std::random_device rd;
    std::shuffle(this->cards.begin(), this->cards.end(), std::default_random_engine(rd()));
}

void Deck::sort() {
    std::sort(std::begin(this->cards), std::end(this->cards), [](Card *a, Card *b) {
        return getCardType(a) < getCardType(b);
    });
}

void Deck::clearDeck() {
    for (Card *card :this->cards) {
        delete card;
    }
    this->cards.clear();
    this->monsterCardsCount = 0;
    this->magicCardsCount = 0;
    this->pendulumCardsCount = 0;
}

std::ostream &operator<<(std::ostream &out, Deck &deck) {
    // sort the deck, so that cards are correctly ordered
    // method sort() is not const, therefore Deck cannot be made const and operator<< cannot be made const
    deck.sort();
    // print the name and card counts
    out << deck.name << "|" << deck.getCardCount() << "|" << deck.getMonsterCardCount() << "|"
        << deck.getMagicCardCount() << "|"
        << deck.getPendulumCardCount() << "\n";
    // print all the cards
    for (Card *card: deck.cards) {
        out << *card << "\n";
    }
    return out;
}

std::istream &operator>>(std::istream &in, Deck &deck) {
    deck.clearDeck();
    // delimiter character separating data
    char delimChar = '|';
    // temporary variables to store the corresponding cards before storage
    MonsterCard monsterTemp;
    MagicCard magicTemp;
    PendulumCard pendulumTemp;
    // get the name
    getline(in, deck.name, delimChar);
    // get the card count
    // reading the total card number as monster card number because it's useless
    in >> deck.monsterCardsCount >> delimChar >> deck.monsterCardsCount >> delimChar >> deck.magicCardsCount
       >> delimChar >> deck.pendulumCardsCount;
    // ignore the '\n' symbol which will cause a wrong name of the first card
    in.ignore();
    // read all the monster cards
    for (int i = 0; i < deck.monsterCardsCount; i++) {
        in >> monsterTemp;
        if (in.get() == '\n') {
            deck.cards.push_back(new MonsterCard(monsterTemp));
        }
    }
    // read all the magic cards
    for (int i = 0; i < deck.magicCardsCount; i++) {
        in >> magicTemp;
        deck.cards.push_back(new MagicCard(magicTemp));
    }
    // read all the pendulum cards
    for (int i = 0; i < deck.pendulumCardsCount; i++) {
        in >> pendulumTemp;
        deck.cards.push_back(new PendulumCard(pendulumTemp));
    }
    return in;
}

unsigned short Deck::getCardType(Card *card) {
    if (dynamic_cast<PendulumCard *>(card)) {
        return PENDULUM_CARD_PRIORITY;
    }
    if (dynamic_cast<MagicCard *>(card)) {
        return MAGIC_CARD_PRIORITY;
    }
    if (dynamic_cast<MonsterCard *>(card)) {
        return MONSTER_CARD_PRIORITY;
    }
    return 0;
}

