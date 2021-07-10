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

#ifndef PRACTICUMHW_DUELIST_HPP
#define PRACTICUMHW_DUELIST_HPP

#include "Deck.hpp"
#include "MonsterCard.hpp"
#include "MagicCard.hpp"

class Duelist {
public:
    Duelist(const std::string &name = "");

    Duelist(const std::string &name, const Deck &deck);

    Duelist(const Duelist &duelist);

    void changeMonsterCardInDeck(const unsigned int &index, const MonsterCard &monsterCard);

    void changeMagicCardInDeck(const unsigned int &index, const MagicCard &magicCard);

    void changePendulumCardInDeck(const unsigned int &index, const PendulumCard &pendulumCard);

    void addMonsterCardInDeck(const MonsterCard &monsterCard);

    void addMagicCardInDeck(const MagicCard &magicCard);

    void addPendulumCardInDeck(const PendulumCard &pendulumCard);

    Deck &getDeck();

    bool writeInFile(const std::string &fileDirectory);

    bool readFromFile(const std::string &FileDirectory);

private:
    std::string name;
    Deck deck;
};

#endif //PRACTICUMHW_DUELIST_HPP
