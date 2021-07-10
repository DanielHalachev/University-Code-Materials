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

#ifndef PRACTICUMHW_DECK_HPP
#define PRACTICUMHW_DECK_HPP

#include <vector>
#include "MonsterCard.hpp"
#include "MagicCard.hpp"
#include "PendulumCard.hpp"

class Deck {
public:
    Deck(const std::string &name = "");

    Deck(const Deck &deck);

    Deck &operator=(const Deck &other);

    std::string getName() const;

    unsigned int getMonsterCardCount() const;

    unsigned int getMagicCardCount() const;

    unsigned int getPendulumCardCount() const;

    void addMonsterCard(const MonsterCard &monsterCard);

    void addMagicCard(const MagicCard &magicCard);

    void addPendulumCard(const PendulumCard &pendulumCard);

    bool changeMonsterCard(const unsigned int &index, const MonsterCard &monsterCard);

    bool changeMagicCard(const unsigned int &index, const MagicCard &magicCard);

    bool changePendulumCard(const unsigned int &index, const PendulumCard &pendulumCard);

    void clearDeck();

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    friend std::istream &operator>>(std::istream &in, Deck &deck);

//    void setName(const std::string &newName);
private:
    std::vector<MonsterCard> monsterCards;
    std::vector<MagicCard> magicCards;
    std::vector<PendulumCard> pendulumCards;
    std::string name;
};

#endif //PRACTICUMHW_DECK_HPP
