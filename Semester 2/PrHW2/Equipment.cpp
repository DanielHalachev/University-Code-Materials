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

// Equipment<> is implemented through complete specialization of Equipment<Armor> and Backpack<Weapon>.
// In this case, the implementation of the methods should be either in a .cpp file or the methods should be declared inline.
// Otherwise, since the methods don't depend on a parameter anymore, they will appear as "multiple definitions".
// I preferred to implement the methods in a .cpp file because it improves readability
// and resembles the standard non-template classes.
#include "Equipment.hpp"

Equipment<Armor>::Equipment() {
    this->slots = 0;
}


bool Equipment<Armor>::isEmpty() const {
    return (slots == 0);
}

bool Equipment<Armor>::isFull() const {
    return (slots == MAX_SLOTS);
}

void Equipment<Armor>::clear() {
    this->armorEquipment.clear();
    this->slots = 0;
}

bool Equipment<Armor>::add(const Armor &object) {
    if (this->slots + 1 > MAX_SLOTS) {
        return false;
    }
    this->armorEquipment.push_back(object);
    this->slots++;
    return true;
}

bool Equipment<Armor>::remove(const Armor &object) {
    int i = 0;
    for (const Armor &armor: this->armorEquipment) {
        if (armor == object) {
            this->armorEquipment.erase(this->armorEquipment.begin() + i);
            this->slots--;
            return true;
        } else {
            i++;
        }
    }
    return false;
}

Armor Equipment<Armor>::getBestEquipment() const {
    double maxScore = this->armorEquipment[0].getGearScore();
    int index = 0;
    for (int i = 1; i < this->armorEquipment.size(); i++) {
        if (this->armorEquipment[i].getGearScore() > maxScore) {
            maxScore = armorEquipment[i].getGearScore();
            index = i;
        }
    }
    return this->armorEquipment[index];
}

unsigned int Equipment<Armor>::getSlots() const {
    return this->slots;
}

bool Equipment<Armor>::operator==(const Equipment<Armor> &other) {
    return (this->totalScore() == other.totalScore());
}

bool Equipment<Armor>::operator!=(const Equipment<Armor> &other) {
    return (this->totalScore() != other.totalScore());
}

double Equipment<Armor>::totalScore() const {
//    double temp = 0;
//    for (const Armor &armor : this->armorEquipment) {
//        temp = temp + armor.getGearScore();
//    }
//    return temp;
    return this->getBestEquipment().getGearScore();
}

std::ostream &operator<<(std::ostream &out, const Equipment<Armor> &object) {
    for (int i = 0; i < SEPARATOR_LIMIT; i++) {
        out << "-";
    }
    out << "\nEquipment Gearscore: " << object.totalScore() << "\nEquipment slots: " << object.slots
        << "\nEquipment contains:\n";
    for (const Armor &armor: object.armorEquipment) {
        out << armor << "\n";
    }
    for (int i = 0; i < SEPARATOR_LIMIT; i++) {
        out << "_";
    }
    out << "\n";
    return out;
}

Equipment<Weapon>::Equipment() {
    this->slots = 0;
}


bool Equipment<Weapon>::isEmpty() const {
    return (slots == 0);
}

bool Equipment<Weapon>::isFull() const {
    return (slots == MAX_SLOTS);
}

void Equipment<Weapon>::clear() {
    this->weaponEquipment.clear();
    this->slots = 0;
}

bool Equipment<Weapon>::add(const Weapon &object) {
    int slotsForObject = 2;
    // in case the type is ONE_HANDED, change
    // if it's not, that means it takes up 2 slots
    if (object.getWeaponType() == ONE_HANDED) {
        slotsForObject = 1;
    }
    if (this->slots + slotsForObject > MAX_SLOTS) {
        return false;
    }
    this->weaponEquipment.push_back(object);
    this->slots = this->slots + slotsForObject;
    return true;
}

bool Equipment<Weapon>::remove(const Weapon &object) {
    int slotsForObject = 2;
    // in case the type is ONE_HANDED, change
    // if it's not, that means it takes up 2 slots
    if (object.getWeaponType() == ONE_HANDED) {
        slotsForObject = 1;
    }
    int i = 0;
    for (const Weapon &weapon: this->weaponEquipment) {
        if (weapon == object) {
            this->weaponEquipment.erase(this->weaponEquipment.begin() + i);
            this->slots = this->slots - slotsForObject;
            return true;
        } else {
            i++;
        }
    }
    return false;
}

Weapon Equipment<Weapon>::getBestEquipment() const {
    double maxScore = this->weaponEquipment[0].getWeaponScore();
    int index = 0;
    for (int i = 1; i < weaponEquipment.size(); i++) {
        if (this->weaponEquipment[i].getWeaponScore() > maxScore) {
            maxScore = weaponEquipment[i].getWeaponScore();
            index = i;
        }
    }
    return this->weaponEquipment[index];
}

unsigned int Equipment<Weapon>::getSlots() const {
    return this->slots;
}

bool Equipment<Weapon>::operator==(const Equipment<Weapon> &other) {
    return (this->totalScore() == other.totalScore());
}

bool Equipment<Weapon>::operator!=(const Equipment<Weapon> &other) {
    return (this->totalScore() != other.totalScore());
}

double Equipment<Weapon>::totalScore() const {
//    double temp = 0;
//    for (const Weapon &weapon : this->weaponEquipment) {
//        temp = temp + weapon.getWeaponScore();
//    }
//    return temp;
    return this->getBestEquipment().getWeaponScore();
}

std::ostream &operator<<(std::ostream &out, const Equipment<Weapon> &object) {
    for (int i = 0; i < SEPARATOR_LIMIT; i++) {
        out << "-";
    }
    out << "\nEquipment Weapon score: " << object.totalScore() << "\nEquipment slots: " << object.slots
        << "\nEquipment contains:\n";
    for (const Weapon &weapon: object.weaponEquipment) {
        out << weapon << "\n";
    }
    for (int i = 0; i < SEPARATOR_LIMIT; i++) {
        out << "_";
    }
    out << "\n";
    return out;
}