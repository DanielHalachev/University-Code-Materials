/**
* Solution to homework assignment 1
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Daniel Halachev
* @idnumber 62547
* @task 2
* @compiler GCC
*/

#ifndef PRACTICUMHW_MONSTERCARD_HPP
#define PRACTICUMHW_MONSTERCARD_HPP

#define MONSTER_NAME_SIZE 26

class MonsterCard {
public:
    MonsterCard();

    MonsterCard(const char name[], unsigned int attack, unsigned int defense);

    bool cardIsEmpty() const;

    const char *getName() const;

    unsigned int getAttack() const;

    unsigned int getDefense() const;

private:
    char name[MONSTER_NAME_SIZE]{};
    unsigned int attackPoints;
    unsigned int defensePoints;
    bool isEmpty;
};

#endif //PRACTICUMHW_MONSTERCARD_HPP
