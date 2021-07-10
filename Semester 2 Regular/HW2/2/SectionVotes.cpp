
#include "SectionVotes.hpp"
#include "iostream"

SectionVotes::SectionVotes() {
    this->party1Votes = 0;
    this->party2Votes = 0;
    this->party3Votes = 0;
}

SectionVotes::SectionVotes(int party1Votes, int party2Votes, int party3Votes) {
    this->party1Votes = party1Votes;
    this->party2Votes = party2Votes;
    this->party3Votes = party3Votes;
}

int SectionVotes::votesForParty(Party party) const {
    switch (party) {
        case 0:
            return this->party1Votes;
        case 1:
            return this->party2Votes;
        case 2:
            return this->party3Votes;
        default:
            return 0;
    }
}

void SectionVotes::setParty1Votes(const int &votes) {
    this->party1Votes = votes;
}

void SectionVotes::setParty2Votes(const int &votes) {
    this->party2Votes = votes;
}

void SectionVotes::setParty3Votes(const int &votes) {
    this->party3Votes = votes;
}

std::ostream &operator<<(std::ostream &out, const SectionVotes &votes) {
    out << votes.party1Votes << " " << votes.party2Votes << " " << votes.party3Votes << "\n";
    return out;
}

std::istream &operator>>(std::istream &in, SectionVotes &votes) {
    in >> votes.party1Votes >> votes.party2Votes >> votes.party3Votes;
    return in;
}

