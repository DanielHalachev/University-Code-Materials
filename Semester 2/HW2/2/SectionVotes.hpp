#pragma once

#include "iostream"
// Add whatever else is required to exist in or out the class
// as well as whatever you think is good to be declared too

enum Party {
    PARTY1 = 0,
    PARTY2 = 1,
    PARTY3 = 2,
};

class SectionVotes {

public:

    SectionVotes();

    SectionVotes(int party1Votes, int party2Votes, int party3Votes);

    int votesForParty(Party) const;

    void setParty1Votes(const int &votes);

    void setParty2Votes(const int &votes);

    void setParty3Votes(const int &votes);


    friend std::ostream &operator<<(std::ostream &out, const SectionVotes &votes);

    friend std::istream &operator>>(std::istream &in, SectionVotes &votes);


private:
    int party1Votes;
    int party2Votes;
    int party3Votes;

};


