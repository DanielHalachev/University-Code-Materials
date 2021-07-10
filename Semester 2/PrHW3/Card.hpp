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

#ifndef PRHW3_CARD_HPP
#define PRHW3_CARD_HPP

#include <string>

class Card {
public:
    Card(const std::string &name = "", const std::string &effect = "");

    std::string getName() const;

    std::string getEffect() const;

//    void setName(std::string &name);
//
//    void setEffect(std::string &effect);

protected:
    std::string name;
    std::string effect;
};


#endif //PRHW3_CARD_HPP
