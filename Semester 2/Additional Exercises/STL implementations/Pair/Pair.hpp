
#ifndef EXERCISES_PAIR_HPP
#define EXERCISES_PAIR_HPP

#include <iostream>

template<typename S, typename T>
class Pair;

template<typename S, typename T>
std::ostream &operator<<(std::ostream &out, const Pair<S, T> &pair);

template<>
class Pair<int, int> {
public:
    Pair() = default;

    Pair(const int &a, const int &b);

    friend std::ostream &operator
    <<(
            std::ostream &out,
            const Pair<int, int> &pair
    ) {
        out << pair.first << ", " << pair.second;
        return out;
    }

public:
    int first;
    int second;
};

template<>
class Pair<char, char> {
public:
    Pair() = default;

    Pair(const char &a, const char &b);

    friend std::ostream &operator
    <<(
            std::ostream &out,
            const Pair<char, char> &pair
    );

public:
    char first;
    char second;
};


#endif //EXERCISES_PAIR_HPP
