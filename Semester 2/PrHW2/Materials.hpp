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

#ifndef PRACTICUMHW_MATERIALS_HPP
#define PRACTICUMHW_MATERIALS_HPP

#include "iostream"

enum MATERIALS_TYPE {
    herbs, ores, cloth, essence
};

class Materials {
public:
    Materials();

    Materials(const unsigned int &herbs, const unsigned int &ores, const unsigned int &cloth,
              const unsigned int &essence);

    unsigned int getHerbsCount() const;

    unsigned int getOresCount() const;

    unsigned int getClothCount() const;

    unsigned int getEssenceCount() const;

    void setHerbs(const unsigned int &herbs);

    void setOres(const unsigned int &ores);

    void setCloth(const unsigned int &cloth);

    void setEssence(const unsigned int &essence);

    void setMaterials(const unsigned int &herbs, const unsigned int &ores, const unsigned int &cloth,
                      const unsigned int &essence);

    /// Material slots calculations are complicated and this method returns the occupied slots
    unsigned int calculateSlots() const;

    friend std::ostream &operator<<(std::ostream &out, const Materials &materials);


private:
    unsigned int herbsCount;
    unsigned int oresCount;
    unsigned int clothCount;
    unsigned int essenceCount;
};


#endif //PRACTICUMHW_MATERIALS_HPP
