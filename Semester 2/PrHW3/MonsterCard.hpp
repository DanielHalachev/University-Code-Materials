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

#ifndef PRACTICUMHW_MONSTERCARD_HPP
#define PRACTICUMHW_MONSTERCARD_HPP


#include "Card.hpp"
#include "iostream"

class MonsterCard : virtual public Card {
public:
    MonsterCard();

    MonsterCard(const std::string &name, const std::string &effect, const unsigned int &attack,
                const unsigned int &defense);

    unsigned int getAttack() const;

    unsigned int getDefense() const;

    friend std::ostream &operator<<(std::ostream &out, const MonsterCard &monsterCard);

    friend std::istream &operator>>(std::istream &in, MonsterCard &monsterCard);

//    void setAttack(const unsigned int &attack);

//    void setDefence(const unsigned int &defense);

    //getters and setters from Card.hpp

protected:
    unsigned int attackPoints;
    unsigned int defensePoints;
    // std::string name         from Card.hpp
    //std::string effect        from Card.hpp
};

#endif //PRACTICUMHW_MONSTERCARD_HPP
