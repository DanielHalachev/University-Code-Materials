/**
* Solution to homework assignment 3
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Daniel Halachev
* @idnumber 62547
* @task 1
* @compiler GCC
*/

#include <iostream>
#include "Duelist.hpp"

int main() {
    MonsterCard mon1("Gajev", "Does 2.66", 100, 50);
    MonsterCard mon2("Dichev", "Does exams", 50, 0);
    MagicCard mag1("Sariev", "Automates automata", MagicCard::BUFF);
    MagicCard mag2("Eugenius", "Solves integrals", MagicCard::SPELL);
    PendulumCard pen1("Tsankov", "Draws nicely", 50, 50, MagicCard::SPELL, 13);
//    return 0;
    Deck d1("Kotaka's Deck");
    d1.addMagicCard(mag1);
    d1.addMagicCard(mag2);
    d1.addMonsterCard(mon1);
    d1.addMonsterCard(mon2);
    d1.addPendulumCard(pen1);
    std::cout << "\nDeck after creation:" << std::endl;
    std::cout << d1;
//    return 0;
    Duelist student("Kotaka", d1);
    student.changeMonsterCardInDeck(0, MonsterCard("Gajev", "Does 6.00", 100, 50));
    student.addMagicCardInDeck(MagicCard("Natali", "Gives homework", MagicCard::TRAP));
    std::cout << "\nDeck of Duelist:" << std::endl;
    std::cout << student.getDeck();
    student.writeInFile("Kotaka.txt");
    Duelist student2;
    student2.readFromFile("Kotaka.txt");
    std::cout << "\nNewStudent:\n" << student2.getDeck();
    return 0;
}
