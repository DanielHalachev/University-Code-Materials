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

#ifndef PRACTICUMHW_ARMOR_HPP
#define PRACTICUMHW_ARMOR_HPP

#include <string>
#include <vector>
#include "iostream"

enum ArmorType {
    CLOTH, LEATHER, MAIL
};

class Armor {
public:
    Armor();

    ArmorType getArmorType() const;

    unsigned int getDefense() const;

    double getGearScore() const;

    void changeArmorType(const ArmorType &newType);

    /// returns bool so that negative numbers can be refused
    bool addEffect(const std::pair<std::string, double> &effect);

    /// returns bool so that negative values can be refused
    bool addEffect(const std::string &effectName, const double &effectValue);

    ///removes effect by full match
    bool removeEffect(const std::pair<std::string, double> &effect);

    ///removes effect by name
    bool removeEffect(const std::string &effectName);

    ///changes effect by full match
    bool changeEffect(const std::pair<std::string, double> &oldEffect,
                      const std::pair<std::string, double> &newEffect);

    ///changes effect by name
    bool changeEffect(const std::string &oldEffectName,
                      const std::pair<std::string, double> &newEffect);

    bool operator==(const Armor &other) const;

    friend std::ostream &operator<<(std::ostream &out, const Armor &armor);

private:
    ArmorType type;
    unsigned int defense;
    std::vector<std::pair<std::string, double>> effects;
    std::vector<double> gearScore;
};


#endif //PRACTICUMHW_ARMOR_HPP
