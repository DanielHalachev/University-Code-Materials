https://www.hackerrank.com/contests/sda-hw-5/challenges/lekcii


#include <iostream>
#include <algorithm>


#define MAX_CHAR 256

int main() {
    std::string str;
    std::cin >> str;
    long l = str.length();

    long counts[MAX_CHAR];
    long map[MAX_CHAR];

    for (int i = 0; i < MAX_CHAR; i++) {
        map[i] = l;
        // set all counts to 0
        counts[i] = 0;
    }

    for (long i = 0; i < l; i++) {
        // get current
        char x = str[i];
        // increase count, as it's seen more than once
        counts[x]++;
        if (counts[x] == 1) {
            map[x] = i;
        }
        if (counts[x] >= 2) {
            map[x] = l;
        }
    }
    std::sort(map, map + MAX_CHAR);
    for (long i: map) {
        if (i != l) {
            std::cout << i << " ";
        }
    }
}
