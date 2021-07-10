/**
* Solution to homework assignment 2
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Daniel Halachev
* @idnumber 62547
* @task 1
* @compiler GCC
*/

#ifndef PRACTICUMHW_MONEY_HPP
#define PRACTICUMHW_MONEY_HPP

#include "iostream"

class Money {
public:
    Money();

    Money(const unsigned int &moneyInSilver);

    unsigned int getQuantity() const;

    unsigned int getSilver() const;

    unsigned int getGold() const;

    /// changes money quantity outright
    void setMoney(const unsigned int &newQuantity);

    /// adds money in gold format
    void addGold(const unsigned int &gold);

    /// adds money in silver format
    void addSilver(const unsigned int &silver);

    /// removes money from the total quantity in gold format
    bool subtractGold(unsigned int &gold);

    /// removes money from the total quantity in silver format
    bool subtractSilver(unsigned int &silver);

    friend std::ostream &operator<<(std::ostream &out, const Money &money);


private:
    unsigned int quantity;
};


#endif //PRACTICUMHW_MONEY_HPP
