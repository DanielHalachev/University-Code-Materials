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

#ifndef PRACTICUMHW_INVENTORY_HPP
#define PRACTICUMHW_INVENTORY_HPP

#define SEPARATOR_LIMIT 40

#include "iostream"

template<class T>
class Inventory;

template<class T>
std::ostream &operator<<(std::ostream &out, const Inventory<T> &inventory);

template<class T>
class Inventory {
public:
    Inventory();

    Inventory(const T &object);

    bool operator==(const Inventory<T> &other);

    bool operator!=(const Inventory<T> &other);

    void setContent(const T &object);

    void clear();

    friend std::ostream &operator
    <<<>(
    std::ostream &out,
    const Inventory<T> &inventory
    );

private:
    T inventory;
};

template<class T>
Inventory<T>::Inventory() = default;

template<class T>
Inventory<T>::Inventory(const T &object) {
    this->inventory = object;
}

template<class T>
void Inventory<T>::setContent(const T &object) {
    this->inventory = object;
}

template<class T>
void Inventory<T>::clear() {
    this->inventory.clear();
}

template<class T>
bool Inventory<T>::operator==(const Inventory<T> &other) {
    return (this->inventory.getSlots() == other.inventory.getSlots());
}

template<class T>
bool Inventory<T>::operator!=(const Inventory<T> &other) {
    return (this->inventory.getSlots() != other.inventory.getSlots());
}

template<class T>
std::ostream &operator<<(std::ostream &out, const Inventory<T> &inventory) {
    for (int i = 0; i < SEPARATOR_LIMIT; i++) {
        out << "-";
    }
    out << "\n";
    out << "Slots used: " << inventory.inventory.getSlots() << "\n" << inventory.inventory;
    for (int i = 0; i < SEPARATOR_LIMIT; i++) {
        out << "";
    }
    return out;
}


#endif //PRACTICUMHW_INVENTORY_HPP
