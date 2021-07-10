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

#ifndef PRACTICUMHW_WEAPON_HPP
#define PRACTICUMHW_WEAPON_HPP

#define ONE_HAND_MODIFIER 0.75

#define TWO_HANDS_MODIFIER 1.5

#include <vector>
#include <map>
#include <string>
#include "iostream"


enum WeaponType {
    ONE_HANDED, TWO_HANDED
};

class Weapon {
public:


    Weapon();

    std::string getName() const;

    WeaponType getWeaponType() const;

    std::pair<double, double> getHitDamage() const;

    double getWeaponScore() const;

    bool setName(const std::string &newName);

    void changeWeaponType(const WeaponType &newType);

    void setHitDamage(const std::pair<double, double> &newHitDamage);

    /// returns bool so that negative values can be refused
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

    bool operator==(const Weapon &other) const;

    friend std::ostream &operator<<(std::ostream &out, const Weapon &weapon);

private:
    std::string name;
    WeaponType type;
    std::pair<double, double> hitDamage;
    std::vector<std::pair<std::string, double>> effects;
    // allowed weapon types will be defined by the user here
    // e.g. even if a dagger can be two-handed according to the user, that's OK
    // the member will be filled with every new unique weaponName-weaponType combination
    // and will act as a dictionary for any new weapon, which is created
    static std::map<std::string, WeaponType> weaponTypes;
};


#endif //PRACTICUMHW_WEAPON_HPP
