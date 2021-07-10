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

// Backpack<> is implemented through complete specialization of Backpack<Money> and Backpack<Materials>.
// In this case, the implementation of the methods should be either in a .cpp file or the methods should be declared inline.
// Otherwise, since the methods don't depend on a parameter anymore, they will appear as "multiple definitions".
// I preferred to implement the methods in a .cpp file because it improves readability
// and resembles the standard non-template classes.

#include "Backpack.hpp"

Backpack<Money>::Backpack() {
    this->money.setMoney(0);
}

bool Backpack<Money>::isEmpty() const {
    return (this->money.getQuantity() == 0);
}

//method is static, no const
bool Backpack<Money>::isFull() {
    return false;
}

void Backpack<Money>::clear() {
    this->money.setMoney(0);
}

void Backpack<Money>::add(const Money &object) {
    this->money.setMoney(object.getQuantity());
}

bool Backpack<Money>::remove(const Money &object) {
    if (this->money.getQuantity() < object.getQuantity()) {
        return false;
    }
    unsigned int silver = object.getSilver();
    this->money.subtractSilver(silver);
    return true;
}

// method is static, no const
unsigned int Backpack<Money>::getSlots() {
    return 0;
}

template<>
std::ostream &operator<<(std::ostream &out, const Backpack<Money> &object) {
    for (int i = 0; i < SEPARATOR_LIMIT; i++) {
        out << "-";
    }
    out << "\nBackpack contains:" << object.money;
    for (int i = 0; i < SEPARATOR_LIMIT; i++) {
        out << "_";
    }
    out << "\n";
    return out;
}

// Begin Backpack<Materials> implementation
Backpack<Materials>::Backpack() {
    this->slots = 0;
    this->materials.setMaterials(0, 0, 0, 0);
}

bool Backpack<Materials>::isEmpty() const {
    return (this->slots == 0);
}

bool Backpack<Materials>::isFull() const {
    return (this->slots == MATERIALS_MAX_SLOTS);
}

void Backpack<Materials>::clear() {
    this->materials.setMaterials(0, 0, 0, 0);
    this->slots = 0;
}

bool Backpack<Materials>::add(const Materials &object) {
    unsigned int herbs = this->materials.getHerbsCount() + object.getHerbsCount();
    unsigned int ores = this->materials.getOresCount() + object.getOresCount();
    unsigned int cloth = this->materials.getClothCount() + object.getClothCount();
    unsigned int essence = this->materials.getEssenceCount() + object.getEssenceCount();

    Materials result(herbs, ores, cloth, essence);
    // can't add more than the slots allow
    if (result.calculateSlots() > MATERIALS_MAX_SLOTS) {
        return false;
    }
    this->materials = result;
    this->slots = materials.calculateSlots();
    return true;
}

bool Backpack<Materials>::remove(const Materials &object) {
    int herbs = this->materials.getHerbsCount() - object.getHerbsCount();
    int ores = this->materials.getOresCount() - object.getOresCount();
    int cloth = this->materials.getClothCount() - object.getClothCount();
    int essence = this->materials.getEssenceCount() - object.getEssenceCount();
    // can't subtract more than there currently is
    if (herbs < 0 || ores < 0 || cloth < 0 || essence < 0) {
        return false;
    }
    this->materials.setMaterials(herbs, ores, cloth, essence);
    this->slots = materials.calculateSlots();
    return true;
}

unsigned int Backpack<Materials>::getSlots() const {
    return this->slots;
}

template<>
std::ostream &operator<<(std::ostream &out, const Backpack<Materials> &object) {
    for (int i = 0; i < SEPARATOR_LIMIT; i++) {
        out << "-";
    }
    out << "\nBackpack contains: " << object.materials;
    for (int i = 0; i < SEPARATOR_LIMIT; i++) {
        out << "_";
    }
    out << "\n";
    return out;
}