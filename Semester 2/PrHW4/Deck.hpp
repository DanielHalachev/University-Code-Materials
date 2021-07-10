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

#ifndef PRACTICUMHW_DECK_HPP
#define PRACTICUMHW_DECK_HPP

// the lower the number, the bigger the priority
#define PENDULUM_CARD_PRIORITY 3
#define MAGIC_CARD_PRIORITY 2
#define MONSTER_CARD_PRIORITY 1

#include <vector>
#include "MonsterCard.hpp"
#include "MagicCard.hpp"
#include "PendulumCard.hpp"

class Deck {
public:
    Deck(const std::string &name = "");

    ~Deck();

    Deck(const Deck &deck);

    Deck &operator=(const Deck &other);

    std::string getName() const;

    unsigned int getMonsterCardCount() const;

    unsigned int getMagicCardCount() const;

    unsigned int getPendulumCardCount() const;

    unsigned int getCardCount() const;

    Card &getCard(const unsigned int &index) const;

    void addCard(Card *card);

    bool changeCard(const unsigned int &index, Card *card);

    void shuffle() ;

    void sort() ;

    void clearDeck();

    friend std::ostream &operator<<(std::ostream &out, Deck &deck);

    friend std::istream &operator>>(std::istream &in, Deck &deck);

    void setName(const std::string &newName);

private:
    std::vector<Card *> cards;
    std::string name;
    unsigned int magicCardsCount;
    unsigned int monsterCardsCount;
    unsigned int pendulumCardsCount;

    // returns a number, corresponding to the card order
    // convenient for comparing Card* objects
    static unsigned short getCardType(Card *card);
};

#endif //PRACTICUMHW_DECK_HPP
