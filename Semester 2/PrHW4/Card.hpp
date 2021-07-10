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

#ifndef PRHW3_CARD_HPP
#define PRHW3_CARD_HPP

#include <string>

class Card {
public:
    Card(const std::string &name = "", const std::string &effect = "", const unsigned int &rarity = 0);

    virtual Card *clone() const = 0;

    std::string getName() const;

    std::string getEffect() const;

    unsigned int getRarity() const;

    bool operator<(const Card &other) const;

    bool operator>(const Card &other) const;

    friend std::ostream &operator<<(std::ostream &out, const Card &card);

    friend std::istream &operator>>(std::istream &in, Card &card);

    virtual std::ostream &print(std::ostream &out) const = 0;

    virtual std::istream &read(std::istream &in) = 0;

    virtual ~Card() = default;

//    void setName(std::string &name);
//
//    void setEffect(std::string &effect);
//
//    void setRarity(unsigned int newRarity);

protected:
    std::string name;
    std::string effect;
    unsigned int rarity;
};


#endif //PRHW3_CARD_HPP
