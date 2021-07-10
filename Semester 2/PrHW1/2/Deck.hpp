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

#ifndef PRACTICUMHW_DECK_HPP
#define PRACTICUMHW_DECK_HPP

#include "MonsterCard.hpp"
#include "MagicCard.hpp"

#define MAGIC_DECK_SIZE 20
#define MONSTER_DECK_SIZE 20

class Deck {
public:
    Deck();

    Deck(const Deck &deck);

    Deck &operator=(const Deck &other);

    ~Deck();

    unsigned int getMonsterCardCount() const;

    unsigned int getMagicCardCount() const;

    void addMonsterCard(MonsterCard monsterCard);

    void addMagicCard(MagicCard &magicCard);

    void changeMonsterCard(unsigned int index, MonsterCard monsterCard);

    void changeMagicCard(unsigned int index, MagicCard magicCard);

    //convenient printing function
    void printDeck() const;

private:
    MagicCard *magicCards;
    MonsterCard *monsterCards;
    unsigned short magicSize;
    unsigned short monsterSize;
};

#endif //PRACTICUMHW_DECK_HPP
