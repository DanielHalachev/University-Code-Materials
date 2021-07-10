#include <iostream>
#include "Duelist.hpp"

int main() {
    MonsterCard mon1("Gajev", "Does 2.66", 5, 100, 50);
    MonsterCard mon2("Dichev", "Does exams", 2, 50, 0);
    MagicCard mag1("Sariev", "Automates automata", 3, MagicCard::BUFF);
    MagicCard mag2("Eugenius", "Solves integrals", 6, MagicCard::SPELL);
    PendulumCard pen1("Tsankov", "Draws nicely", 10, 50, 50, MagicCard::SPELL, 13);
//    return 0;
    Deck d1("Kotaka's Deck");
    d1.addCard(&mag1);
    d1.addCard(&mag2);
    d1.addCard(&mon1);
    d1.addCard(&mon2);
    d1.addCard(&pen1);
    std::cout << "\nDeck after creation:" << std::endl;
    std::cout << d1;
//    return 0;
    Duelist student("Kotaka", d1);
    student.changeCardInDeck(0, new MonsterCard("Gajev", "Does 6.00", 10, 100, 50));
    MagicCard m3("Natali", "Gives homework", 5, MagicCard::TRAP);
    student.addCardInDeck(&m3);
    std::cout << "\nDeck of Duelist:" << std::endl;
    std::cout << student.getDeck();
    student.writeInFile("Kotaka.txt");
    Duelist student2;
    student2.readFromFile("Kotaka.txt");
    std::cout << "\nNewStudent:\n" << student2.getDeck();
    student.duel(student2);
    return 0;
}
