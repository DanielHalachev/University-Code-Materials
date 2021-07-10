
#include "ElectionResultsDatabase.hpp"

ElectionResultsDatabase::ElectionResultsDatabase() = default;

void ElectionResultsDatabase::addResultsFromFile(const char *filename) {
    std::ifstream fileDialog;
    fileDialog.open(filename, std::ios::in);
    if (!fileDialog) {
        return;
    }
    SectionVotes section;
    while (fileDialog >> section) {
        this->votesInSections.push_back(section);
    }
    fileDialog.close();
}

int ElectionResultsDatabase::numberOfSections() const {
    return this->votesInSections.size();
}

int ElectionResultsDatabase::votesForParty(Party party) const {
    int temp = 0;
    for (SectionVotes vote:this->votesInSections) {
        temp = temp + vote.votesForParty(party);
    }
    return temp;
}

Party ElectionResultsDatabase::winningParty() const {
    if (this->votesForParty(PARTY1) >= this->votesForParty(PARTY2) &&
        this->votesForParty(PARTY1) >= this->votesForParty(PARTY3)) {
        return PARTY1;
    }
    if (this->votesForParty(PARTY2) >= this->votesForParty(PARTY1) &&
        this->votesForParty(PARTY2) >= this->votesForParty(PARTY3)) {
        return PARTY2;
    }
    return PARTY3;
}

std::ostream &operator<<(std::ostream &out, const ElectionResultsDatabase &database) {
    for (SectionVotes vote: database.votesInSections) {
        out << vote;
    }
    return out;
}

std::istream &operator>>(std::istream &in, ElectionResultsDatabase &database) {
    SectionVotes section;
    while (in >> section) {
        database.votesInSections.push_back(section);
    }
    return in;
}
