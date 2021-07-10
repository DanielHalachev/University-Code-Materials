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

#include "Deck.hpp"
#include "iostream"

Deck::Deck() {
    this->monsterCards = new MonsterCard[MONSTER_DECK_SIZE];
    this->monsterSize = 0;
    this->magicCards = new MagicCard[MAGIC_DECK_SIZE];
    this->magicSize = 0;
}

Deck::Deck(const Deck &deck) {
    this->magicCards = new MagicCard[MAGIC_DECK_SIZE];
    for (int i = 0; i < MAGIC_DECK_SIZE; i++) {
        this->magicCards[i] = deck.magicCards[i];
    }
    this->monsterCards = new MonsterCard[MONSTER_DECK_SIZE];
    for (int i = 0; i < MONSTER_DECK_SIZE; i++) {
        this->monsterCards[i] = deck.monsterCards[i];
    }
    this->magicSize = deck.getMagicCardCount();
    this->monsterSize = deck.getMonsterCardCount();
}

Deck &Deck::operator=(const Deck &other) {
    if (this != &other) {
        delete[] this->monsterCards;
        delete[] this->magicCards;
        this->monsterCards = new MonsterCard[MONSTER_DECK_SIZE];
        this->magicCards = new MagicCard[MAGIC_DECK_SIZE];
        for (int i = 0; i < MONSTER_DECK_SIZE; i++) {
            this->monsterCards[i] = other.monsterCards[i];
        }
        for (int i = 0; i < MAGIC_DECK_SIZE; i++) {
            this->magicCards[i] = other.magicCards[i];
        }
    }
    return *this;
}

Deck::~Deck() {
    delete[] this->magicCards;
    delete[] this->monsterCards;
}

unsigned int Deck::getMonsterCardCount() const {
    return monsterSize;
}

unsigned int Deck::getMagicCardCount() const {
    return magicSize;
}

void Deck::addMagicCard(MagicCard &magicCard) {
    if (magicSize < MAGIC_DECK_SIZE) {
        for (int i = 0; i < MAGIC_DECK_SIZE; i++) {
            if (this->magicCards[i].getType() == MagicCard::none) {
                magicCards[i] = magicCard;
                magicSize++;
                break;
            }
        }
    } else {
        std::cout << "Deck is full. Use <changeMagicCard> instead" << std::endl;
    }
}

void Deck::addMonsterCard(MonsterCard monsterCard) {
    if (monsterSize < MONSTER_DECK_SIZE) {
        for (int i = 0; i < MONSTER_DECK_SIZE; i++) {
            if (monsterCards[i].cardIsEmpty()) {
                this->monsterCards[i] = monsterCard;
                monsterSize++;
                break;
            }
        }
    } else {
        std::cout << "Deck is full. Use <changeMonsterCard> instead" << std::endl;
    }
}

void Deck::changeMagicCard(unsigned int index, MagicCard magicCard) {
    if (index > MAGIC_DECK_SIZE - 1) {
        index = MAGIC_DECK_SIZE - 1;
        std::cout << "Deck index out of range. Changing the last possible card instead" << std::endl;
    } else if (index < 0) {
        index = 0;
        std::cout << "Deck index out of range. Changing the first possible card instead" << std::endl;
    }
    if (magicCards[index].getType() == MagicCard::none) {
        this->magicCards[index] = magicCard;
        magicSize++;
    } else {
        this->magicCards[index] = magicCard;
    }
}

void Deck::changeMonsterCard(unsigned int index, MonsterCard monsterCard) {
    if (index > MONSTER_DECK_SIZE - 1) {
        index = MONSTER_DECK_SIZE - 1;
        std::cout << "Deck index out of range. Changing the last possible card instead" << std::endl;
    } else if (index < 0) {
        index = 0;
        std::cout << "Deck index out of range. Changing the first possible card instead" << std::endl;
    }
    if (this->monsterCards[index].cardIsEmpty()) {
        monsterSize++;
    }
    this->monsterCards[index] = monsterCard;
}

void Deck::printDeck() const {
    std::cout << "Magic Cards:" << std::endl;
    printf("%-6s%-*s%-*s%-s\n", "Ind.", MAGIC_NAME_SIZE, "Name", EFFECT_SIZE - 30, "Effect", "Type");
    for (int i = 0; i < 110; i++) {
        std::cout << "_";
    }
    std::cout << '\n';
    for (int i = 0; i < MAGIC_DECK_SIZE; i++) {
        printf("%-6d%-*s%-*s%-5u\n", i, MAGIC_NAME_SIZE, this->magicCards[i].getName(), EFFECT_SIZE - 30,
               this->magicCards[i].getEffect(), this->magicCards[i].getType());
    }
    std::cout << "\nMonster Cards:" << std::endl;
    for (int i = 0; i < 110; i++) {
        std::cout << "_";
    }
    std::cout << '\n';
    printf("%-6s%-*s%-10s%-10s%-10s\n", "Ind.", MONSTER_NAME_SIZE, "Name", "Attack", "Defense", "Is Empty");
    for (int i = 0; i < MONSTER_DECK_SIZE; i++) {
        printf("%-6d%-*s%-10u%-10u%-10s\n", i, MONSTER_NAME_SIZE, this->monsterCards[i].getName(),
               this->monsterCards[i].getAttack(), this->monsterCards[i].getDefense(),
               (this->monsterCards[i].cardIsEmpty() ? "true" : "false"));
    }
}

