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

#ifndef PRHW3_PENDULUMCARD_HPP
#define PRHW3_PENDULUMCARD_HPP


#define MAX_SCALE 13
#define MIN_SCALE 1

#include "MonsterCard.hpp"
#include "MagicCard.hpp"
#include "iostream"

class PendulumCard : public MonsterCard, public MagicCard {
public:
    PendulumCard();

    PendulumCard(const std::string &name, const std::string &effect, const unsigned int &attack,
                 const unsigned int &defense, const Type &type, const unsigned short &scale);

    unsigned short getScale() const;

    friend std::ostream &operator<<(std::ostream &out, const PendulumCard &pendulumCard);

    friend std::istream &operator>>(std::istream &in, PendulumCard &pendulumCard);
//    bool setScale(const unsigned int &newScale);

    //getters and setters from Card.hpp, MonsterCard.cpp, MagicCard.cpp

private:
    unsigned short scale;
    //std::string name;                 from Card.hpp
    //std:: string effect;              from Card.hpp
    //unsigned int attackPoints;        from MonsterCard.hpp
    //unsigned int defencePoints;       from MonsterCard.hpp
    //Type type;                        from MagicCard.cpp
};


#endif //PRHW3_PENDULUMCARD_HPP
