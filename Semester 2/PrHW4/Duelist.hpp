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

#ifndef PRACTICUMHW_DUELIST_HPP
#define PRACTICUMHW_DUELIST_HPP

#include "Deck.hpp"
#include "MonsterCard.hpp"
#include "MagicCard.hpp"
#include "fstream"

class Duelist {
public:
    Duelist(const std::string &name = "");

    Duelist(const std::string &name, const Deck &deck);

    Duelist(const Duelist &duelist);

    bool changeCardInDeck(const unsigned int &index, Card *card);

    void addCardInDeck(Card *card);

    Deck &getDeck();

    bool writeInFile(const std::string &fileDirectory);

    bool readFromFile(const std::string &FileDirectory);

    bool duel(Duelist &opponent);

    friend bool duel(Duelist &lhs, Duelist &rhs);

private:
    std::string name;
    Deck deck;
};

#endif //PRACTICUMHW_DUELIST_HPP
