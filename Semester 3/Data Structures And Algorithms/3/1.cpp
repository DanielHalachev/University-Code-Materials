https://www.hackerrank.com/contests/sda-hw-3/challenges/challenge-3066

#include <iostream>

// Returns cube root of a no number
long long almostCube(long long number) {
    if(number < 8){
        return number;
    }
    long long base = 1;
    while (base * base * base <= number) {
        ++base;
    }
    base--;

    return base * base * base;
}


long long numberOfPresents(long long number) {
    if (number < 8) {
        return number;
    }
    long long numberOfPresents = 0;
    while (number > 7) {
        number -= almostCube(number);
        numberOfPresents++;
    }
    numberOfPresents += number;
    return numberOfPresents;
}

int main() {
    long long number = 0;
    std::cin >> number;
    std::cout << numberOfPresents(number);
}
