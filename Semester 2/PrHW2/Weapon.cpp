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

#include "Weapon.hpp"
#include "iostream"

// initializing the static member of the Weapon Class, otherwise, the program would crash
std::map<std::string, WeaponType> Weapon::weaponTypes;

Weapon::Weapon() {
    // set Name
    this->name = "";
    // set Weapon Type
    this->type = ONE_HANDED;
    // set Weapon Score
    // set Hit Damage
    this->hitDamage.first = 0;
    this->hitDamage.second = 0;
}

std::string Weapon::getName() const {
    return this->name;
}

WeaponType Weapon::getWeaponType() const {
    return this->type;
}

std::pair<double, double> Weapon::getHitDamage() const {
    return this->hitDamage;
}

double Weapon::getWeaponScore() const {
    double weaponScore = 0;
    for (const std::pair<std::string, double> &effect : this->effects) {
        weaponScore = weaponScore + effect.second;
    }
    if (this->type == ONE_HANDED) {
        weaponScore = weaponScore * ONE_HAND_MODIFIER;
    } else {
        weaponScore = weaponScore * TWO_HANDS_MODIFIER;
    }
    weaponScore = weaponScore + (this->hitDamage.first + this->hitDamage.second) / 2;
    return weaponScore;
}

bool Weapon::setName(const std::string &newName) {
//    // check if a weapon with such name already exists
    if (weaponTypes.find(newName) == weaponTypes.end()) {
        // if no, then remove the old weapon
        weaponTypes.erase(this->name);
        // and add the new weapon
        weaponTypes.insert(std::pair<std::string, WeaponType>(newName, this->type));
        // and change the name
        this->name = newName;
        return true;
    }
    // in case a weapon with the new name exists already
    // terminate the attempt
    return false;
}

void Weapon::setHitDamage(const std::pair<double, double> &newHitDamage) {
    this->hitDamage = newHitDamage;
}

void Weapon::changeWeaponType(const WeaponType &newType) {
    // change the weapon type of the object
    this->type = newType;
    // find the weapon in the database through the name and change its type
    weaponTypes.find(this->name)->second = newType;
}

bool Weapon::addEffect(const std::pair<std::string, double> &effect) {
    if (effect.second < 0) {
        return false;
    }
    this->effects.push_back(effect);
    return true;
}

bool Weapon::addEffect(const std::string &effectName, const double &effectValue) {
    if (effectValue < 0) {
        return false;
    }
    std::pair<std::string, double> effect(effectName, effectValue);
    this->effects.push_back(effect);
    return true;
}

bool Weapon::removeEffect(const std::pair<std::string, double> &effect) {
    // goes through all effects and if it finds a match, removes the effect
    int i = 0;
    for (const std::pair<std::string, double> &pair :this->effects) {
        if (pair == effect) {
            this->effects.erase(this->effects.begin() + i);
            return true;
        } else {
            i++;
        }
    }
    return false;
}

bool Weapon::removeEffect(const std::string &effectName) {
    // goes through all effects and if it finds a match by name, removes the effect
    int i = 0;
    for (const std::pair<std::string, double> &pair :this->effects) {
        if (pair.first == effectName) {
            this->effects.erase(this->effects.begin() + i);
            return true;
        } else {
            i++;
        }
    }
    return false;
}

bool Weapon::changeEffect(const std::pair<std::string, double> &oldEffect,
                          const std::pair<std::string, double> &newEffect) {
    if (newEffect.second < 0) {
        return false;
    }
    // goes through all effects and if it finds a match, changes the effect
    int i = 0;
    for (const std::pair<std::string, double> &pair :this->effects) {
        if (pair == oldEffect) {
            this->effects[i] = newEffect;
            return true;
        } else {
            i++;
        }
    }
    return false;
}


bool Weapon::changeEffect(const std::string &oldEffectName, const std::pair<std::string, double> &newEffect) {
    if (newEffect.second < 0) {
        return false;
    }
    // goes through all effects and if it finds a match by name, changes the effect
    int i = 0;
    for (const std::pair<std::string, double> &pair :this->effects) {
        if (pair.first == oldEffectName) {
            this->effects[i] = newEffect;
            return true;
        } else {
            i++;
        }
    }
    return false;
}

bool Weapon::operator==(const Weapon &other) const {
    return (this->type == other.type && this->hitDamage == other.hitDamage && this->name == other.name &&
            this->getWeaponScore() == other.getWeaponScore());
}

std::ostream &operator<<(std::ostream &out, const Weapon &weapon) {
    out << "Weapon name: " << weapon.name << "\nWeapon type: " << weapon.type << "\nHit Damage: "
        << weapon.hitDamage.first << " - " << weapon.hitDamage.second << "\nWeapon Score: " << weapon.getWeaponScore()
        << "\n";
    for (const std::pair<std::string, double> &pair:weapon.effects) {
        out << pair.first << " " << pair.second << "\n";
    }
    return out;
}


