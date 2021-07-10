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

#ifndef PRACTICUMHW_MAGICCARD_HPP
#define PRACTICUMHW_MAGICCARD_HPP

#include "Card.hpp"
#include "iostream"

class MagicCard : virtual public Card {
public:
    enum Type {
        NONE, TRAP, BUFF, SPELL
    };

    MagicCard();

    MagicCard(const std::string &name, const std::string &effect, const Type &type);

    Type getType() const;

    friend std::ostream &operator<<(std::ostream &out, const MagicCard &magicCard);

    friend std::istream &operator>>(std::istream &in, MagicCard &magicCard);

//    void setType(const Type &type);

    //getters from Card.hpp

protected:
    Type type;
    // std::string name;            from Card.hpp
    // std::string effect;          from Card.hpp
};

#endif //PRACTICUMHW_MAGICCARD_HPP
