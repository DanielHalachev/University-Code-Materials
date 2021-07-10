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

#include "Armor.hpp"

Armor::Armor() {
    this->type = CLOTH;
    this->defense = 0;
}

double Armor::getGearScore() const {
    double result = 0;
    for (const double &effectValue : this->gearScore) {
        result = result + effectValue;
    }
    return result;
}

ArmorType Armor::getArmorType() const {
    return this->type;
}

unsigned int Armor::getDefense() const {
    return this->defense;
}

void Armor::changeArmorType(const ArmorType &newType) {
    this->type = newType;
}

bool Armor::addEffect(const std::pair<std::string, double> &effect) {
    if (effect.second < 0) {
        return false;
    }
    this->effects.push_back(effect);
    this->gearScore.push_back(effect.second);
    return true;
}

bool Armor::addEffect(const std::string &effectName, const double &effectValue) {
    if (effectValue < 0) {
        return false;
    }
    std::pair<std::string, double> effect(effectName, effectValue);
    this->effects.push_back(effect);
    this->gearScore.push_back(effect.second);
    return true;
}

bool Armor::removeEffect(const std::pair<std::string, double> &effect) {
    // goes through all effects and if it finds a match, removes the effect
    int i = 0;
    for (const std::pair<std::string, double> &pair :this->effects) {
        if (pair == effect) {
            this->effects.erase(this->effects.begin() + i);
            break;
        } else {
            i++;
        }
    }
    // in case we go off the limit, something's wrong
    // compare to gearScore size because it's unchanged
    if (i >= this->gearScore.size()) {
        return false;
    }
    // goes through all gearScore values and if it finds a match, removes the value
    // we can expect that the index will be the same, so check:
    if (this->gearScore[i] == effect.second) {
        this->gearScore.erase(this->gearScore.begin() + i);
        return true;
    }
    // in case we don't find the match outright, search
    i = 0;
    for (const unsigned int value:this->gearScore) {
        if (value == effect.second) {
            this->gearScore.erase(this->gearScore.begin() + i);
            return true;
        } else {
            i++;
        }
    }
    return false;
}

bool Armor::removeEffect(const std::string &effectName) {
    // goes through all effects and if it finds a match, removes the effect
    // store the effect value in a temporary
    int temp = 0;
    int i = 0;
    for (const std::pair<std::string, double> &pair :this->effects) {
        if (pair.first == effectName) {
            temp = pair.second;
            this->effects.erase(this->effects.begin() + i);
            break;
        } else {
            i++;
        }
    }
    // in case we go off the limit, something's wrong
    // compare to gearScore size because it's unchanged
    if (i >= this->gearScore.size()) {
        return false;
    }
    // goes through all gearScore values and if it finds a match, removes the value
    // we can expect that the index will be the same, so check:
    if (this->gearScore[i] == temp) {
        this->gearScore.erase(this->gearScore.begin() + i);
        return true;
    }
    // in case we don't find the match outright, search
    i = 0;
    for (const unsigned int value:this->gearScore) {
        if (value == temp) {
            this->gearScore.erase(this->gearScore.begin() + i);
            return true;
        } else {
            i++;
        }
    }
    return false;
}

bool Armor::changeEffect(const std::pair<std::string, double> &oldEffect,
                         const std::pair<std::string, double> &newEffect) {
    if (newEffect.second < 0) {
        return false;
    }
    // goes through all effects and if it finds a match, changes the effect
    int i = 0;
    for (const std::pair<std::string, double> &pair :this->effects) {
        if (pair == oldEffect) {
            this->effects[i] = newEffect;
            break;
        } else {
            i++;
        }
    }
    // in case we go off the limit, something's wrong
    if (i >= this->effects.size()) {
        return false;
    }
    // goes through all gearScore values and if it finds a match, changes the value
    // we can expect that the index will be the same, so check:
    if (this->gearScore[i] == oldEffect.second) {
        this->gearScore[i] = newEffect.second;
        return true;
    }
    // in case we don't find the match outright, search
    i = 0;
    for (const unsigned int value:this->gearScore) {
        if (value == oldEffect.second) {
            this->gearScore[i] = newEffect.second;
            return true;
        } else {
            i++;
        }
    }
    return false;
}

bool Armor::changeEffect(const std::string &oldEffectName, const std::pair<std::string, double> &newEffect) {
    if (newEffect.second < 0) {
        return false;
    }
    // goes through all effects and if it finds a match, changes the effect
    // stores the effect value in a temporary
    int temp = 0;
    int i = 0;
    for (std::pair<std::string, double> &pair :this->effects) {
        if (pair.first == oldEffectName) {
            temp = pair.second;
            pair = newEffect;
            break;
        } else {
            i++;
        }
    }
    // in case we go off the limit, something's wrong
    if (i >= this->effects.size()) {
        return false;
    }
    // goes through all gearScore values and if it finds a match, changes the value
    // we can expect that the index will be the same, so check:
    if (this->gearScore[i] == temp) {
        this->gearScore[i] = newEffect.second;
        return true;
    }
    // in case we don't find the match outright, search
    i = 0;
    for (unsigned int value:this->gearScore) {
        if (value == temp) {
            this->gearScore[i] = newEffect.second;
            return true;
        } else {
            i++;
        }
    }
    return false;
}

bool Armor::operator==(const Armor &other) const {
    return (this->type == other.type && this->getGearScore() == other.getGearScore() && this->defense == other.defense);
}

std::ostream &operator<<(std::ostream &out, const Armor &armor) {
    out << "Armor type: " << armor.type << "\nArmor Defense: " << armor.defense << "\nArmor Gear score: "
        << armor.getGearScore() << "\n";
    for (const std::pair<std::string, double> &pair :armor.effects) {
        out << pair.first << " " << pair.second << "\n";
    }
    return out;
}


