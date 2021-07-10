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

#include "Materials.hpp"

unsigned int roundUp(double number) {
    int integerNumber = (int) number;
    if (number == (double) integerNumber) {
        return integerNumber;
    }
    return integerNumber + 1;
}


Materials::Materials() {
    this->herbsCount = 0;
    this->oresCount = 0;
    this->clothCount = 0;
    this->essenceCount = 0;
}

Materials::Materials(const unsigned int &herbs, const unsigned int &ores, const unsigned int &cloth,
                     const unsigned int &essence) {
    this->herbsCount = herbs;
    this->oresCount = ores;
    this->clothCount = cloth;
    this->essenceCount = essence;
}

unsigned int Materials::getHerbsCount() const {
    return this->herbsCount;
}

unsigned int Materials::getOresCount() const {
    return this->oresCount;
}

unsigned int Materials::getClothCount() const {
    return this->clothCount;
}

unsigned int Materials::getEssenceCount() const {
    return this->essenceCount;
}

void Materials::setHerbs(const unsigned int &herbs) {
    this->herbsCount = herbs;
}

void Materials::setOres(const unsigned int &ores) {
    this->oresCount = ores;
}

void Materials::setCloth(const unsigned int &cloth) {
    this->clothCount = cloth;
}

void Materials::setEssence(const unsigned int &essence) {
    this->essenceCount = essence;
}

void Materials::setMaterials(const unsigned int &herbs, const unsigned int &ores, const unsigned int &cloth,
                             const unsigned int &essence) {
    this->herbsCount = herbs;
    this->oresCount = ores;
    this->clothCount = cloth;
    this->essenceCount = essence;
}

unsigned int Materials::calculateSlots() const {
    return roundUp(this->herbsCount / 20.0) + roundUp(this->oresCount / 20.0) + roundUp(this->clothCount / 20.0) +
           roundUp(this->essenceCount / 10.0);
}

std::ostream &operator<<(std::ostream &out, const Materials &materials) {
    out << "\nMaterials:" << materials.calculateSlots() << " slots used\nHerbs: " << materials.herbsCount << "\nOres: "
        << materials.oresCount << "\nCloth: "
        << materials.clothCount
        << "\nEssence: " << materials.essenceCount << "\n";
    return out;
}
