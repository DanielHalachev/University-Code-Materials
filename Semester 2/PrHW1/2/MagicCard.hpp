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

#ifndef PRACTICUMHW_MAGICCARD_HPP
#define PRACTICUMHW_MAGICCARD_HPP

#define MAGIC_NAME_SIZE 26
#define EFFECT_SIZE 101

class MagicCard {
public:
    enum Type {
        none, trap, buff, spell
    };

    MagicCard();

    MagicCard(const char name[], const char effect[], Type type);

    const char *getName() const;

    const char *getEffect() const;

    Type getType() const;

private:
    char name[MAGIC_NAME_SIZE]{};
    char effect[EFFECT_SIZE]{};
    Type type;
};

#endif //PRACTICUMHW_MAGICCARD_HPP
