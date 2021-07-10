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

#ifndef PRACTICUMHW_BACKPACK_HPP
#define PRACTICUMHW_BACKPACK_HPP


#define MATERIALS_MAX_SLOTS 16

#define SEPARATOR_LIMIT 40

#include "Inventory.hpp"
#include "Money.hpp"
#include "Materials.hpp"
#include "iostream"

template<class T>
class Backpack;

template<class T>
std::ostream &operator<<(std::ostream &out, const Backpack<T> &object);

template<>
class Backpack<Money> {
public:
    Backpack();

    bool isEmpty() const;

    static bool isFull();

    void clear();

    void add(const Money &object);

    bool remove(const Money &object);

    static unsigned int getSlots();

    friend std::ostream &operator
    <<<>(
    std::ostream &out,
    const Backpack<Money> &object
    );

private:
    int slots = 0;
    Money money;
};

template<>
class Backpack<Materials> {
public:
    Backpack();

    bool isEmpty() const;

    bool isFull() const;

    void clear();

    bool add(const Materials &object);

    bool remove(const Materials &object);

    unsigned int getSlots() const;

    friend std::ostream &operator
    <<<>(
    std::ostream &out,
    const Backpack<Materials> &object
    );

private:
    unsigned int slots;
    Materials materials;
};


#endif //PRACTICUMHW_BACKPACK_HPP
