/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Daniel Halachev
* @idnumber 62547
* @task 1
* @compiler GCC
*/

#include <fstream>
#include "Duelist.hpp"

Duelist::Duelist(const std::string &name) {
    this->name = name;
    this->deck = Deck();
}

Duelist::Duelist(const std::string &name, const Deck &deck) {
    this->name = name;
    this->deck = deck;
}

Duelist::Duelist(const Duelist &duelist) {
    this->name = duelist.name;
    this->deck = duelist.deck;
}

Deck &Duelist::getDeck() {
    return (this->deck);
}

bool Duelist::writeInFile(const std::string &fileDirectory) {
    std::ofstream fileDialog;
    // open the file and delete all previous data in it before writing
    fileDialog.open(fileDirectory, std::ios::out);
    if (!fileDialog) {
        return false;
    }
    // operator<< is not const, so the function writeInFile() cannot be made const
    fileDialog << this->deck;
    // close
    fileDialog.close();
    return true;
}

bool Duelist::readFromFile(const std::string &FileDirectory) {
    std::ifstream fileDialog;
    fileDialog.open(FileDirectory);
    if (!fileDialog) {
        return false;
    }
    // if everything's alright, clear the previous data
    this->deck.clearDeck();
    fileDialog >> (this->deck);
    // close
    fileDialog.close();
    return true;
}

bool Duelist::changeCardInDeck(const unsigned int &index, Card *card) {
    return this->deck.changeCard(index, card);
}

void Duelist::addCardInDeck(Card *card) {
    this->deck.addCard(card);
}

bool Duelist::duel(Duelist &opponent) {
    if (this->deck.getCardCount() != opponent.deck.getCardCount()) {
        return false;
    }
    this->deck.shuffle();
    opponent.deck.shuffle();
    int thisScore = 0;      // referred to as LHS score
    int opponentScore = 0;  // referred to as RHS score
    for (int i = 0; i < this->deck.getCardCount(); i++) {
        // check if the RHS score is bigger than the LHS score
        // if yes, increase the RHS score
        // otherwise check if the LHS score is bigger than the RHS score
        // if yes, increase the LHS score
        // if that isn't true either, then do nothing
        (this->deck.getCard(i) < opponent.deck.getCard(i)) ? opponentScore++ :
        (this->deck.getCard(i) > opponent.deck.getCard(i) ? thisScore++ : 1);
    }
    if (thisScore == opponentScore) {
        std::cout << "Draw";
        return true;
    }
    std::cout << ((thisScore < opponentScore) ? opponent.name : this->name) << " won";
    return true;
}

bool duel(Duelist &lhs, Duelist &rhs) {
    // wrote similar code instead of using the non-friend function
    // in order to increase speed
    if (lhs.deck.getCardCount() != rhs.deck.getCardCount()) {
        return false;
    }
    lhs.deck.shuffle();
    rhs.deck.shuffle();
    int lhsScore = 0;
    int rhsScore = 0;
    for (int i = 0; i < lhs.deck.getCardCount(); i++) {
        // check if the RHS score is bigger than the LHS score
        // if yes, increase the RHS score
        // otherwise check if the LHS score is bigger than the RHS score
        // if yes, increase the LHS score
        // if that isn't true either, then do nothing
        (lhs.deck.getCard(i) < rhs.deck.getCard(i)) ? rhsScore++ :
        (lhs.deck.getCard(i) > rhs.deck.getCard(i) ? lhsScore++ : 1);
    }
    if (lhsScore == rhsScore) {
        std::cout << "Draw";
        return true;
    }
    std::cout << ((lhsScore < rhsScore) ? rhs.name : lhs.name) << " won";
    return true;
}


