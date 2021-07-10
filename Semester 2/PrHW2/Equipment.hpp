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

#ifndef PRACTICUMHW_EQUIPMENT_HPP
#define PRACTICUMHW_EQUIPMENT_HPP

#define MAX_SLOTS 24

#define SEPARATOR_LIMIT 40

#include "Armor.hpp"
#include "Weapon.hpp"
#include "iostream"

template<class T>
class Equipment;

template<typename T>
std::ostream &operator<<(std::ostream &out, const Equipment<T> &object);

template<>
class Equipment<Armor> {
public:
    Equipment();

    bool isEmpty() const;

    bool isFull() const;

    void clear();

    bool add(const Armor &object);

    bool remove(const Armor &object);

    Armor getBestEquipment() const;

    unsigned int getSlots() const;

    bool operator==(const Equipment<Armor> &other);

    bool operator!=(const Equipment<Armor> &other);

    friend std::ostream &operator<<(std::ostream &out, const Equipment<Armor> &object);


private:
    unsigned int slots;
    std::vector<Armor> armorEquipment;

    double totalScore() const;
};


template<>
class Equipment<Weapon> {
public:
    Equipment();

    bool isEmpty() const;

    bool isFull() const;

    void clear();

    bool add(const Weapon &object);

    bool remove(const Weapon &object);

    Weapon getBestEquipment() const;

    unsigned int getSlots() const;

    bool operator==(const Equipment<Weapon> &other);

    bool operator!=(const Equipment<Weapon> &other);

    friend std::ostream &operator<<(std::ostream &out, const Equipment<Weapon> &object);

private:
    unsigned int slots;
    std::vector<Weapon> weaponEquipment;

    double totalScore() const;
};

#endif //PRACTICUMHW_EQUIPMENT_HPP
