//
// Created by User on 28.5.2021 г..
//

#include "Pair.hpp"

Pair<char, char>::Pair(const char &a, const char &b) {
    this->first = a;
    this->second = b;
}

Pair<int, int>::Pair(const int &a, const int &b) {
    this->first = a;
    this->second = b;
}

std::ostream &operator
<<(
        std::ostream &out,
        const Pair<char, char> &pair
) {
    out << pair.first<<+"h";

    return out;
}