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

#ifndef PRACTICUMHW_DUELIST_HPP
#define PRACTICUMHW_DUELIST_HPP

#include "Deck.hpp"
#include "MonsterCard.hpp"
#include "MagicCard.hpp"

class Duelist {
public:
    Duelist();

    Duelist(const char name[], Deck &deck);

    Duelist(const Duelist &duelist);

    ~Duelist();

    void changeMonsterCardInDeck(unsigned int index, MonsterCard monsterCard);

    void changeMagicCardInDeck(unsigned int index, MagicCard magicCard);

    void addMonsterCardInDeck(MonsterCard monsterCard);

    void addMagicCardInDeck(MagicCard magicCard);

    // useful function to print deck content
    void printDeck() const;

private:
    char *name;
    Deck deck;
};

#endif //PRACTICUMHW_DUELIST_HPP
