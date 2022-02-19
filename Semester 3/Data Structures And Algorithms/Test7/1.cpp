https://www.hackerrank.com/contests/sda-2021-2022-test-7-final/challenges/challenge-1770

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_set>

int main() {

    int n;
    std::cin >> n;
    std::vector<int> queryVector(n);
    std::map<int, int> occurances;
    std::vector<int> seenOnce;
    std::vector<int> seenMoreThanOnce;

    for (int i = 0; i < n; i++) {
        std::cin >> queryVector[i];
    }

    for (const int q: queryVector) {
        occurances[q]++;
    }

    std::unordered_set<int> alreadySeen;
    for (const int q: queryVector) {
        if (alreadySeen.insert(q).second) {
            if (occurances[q] == 1) {
                seenOnce.push_back(q);
            } else {
                seenMoreThanOnce.push_back(q);
            }
        }
    }

    for (const int number: seenOnce) {
        std::cout << number << ' ';
    }

    for (const int number: seenMoreThanOnce) {
        std::cout << number << ' ';
    }
    return 0;
}
