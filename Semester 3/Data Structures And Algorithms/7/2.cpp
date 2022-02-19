https://www.hackerrank.com/contests/sda-hw-7/challenges/minimum-xor-3

#include <iostream>
#include <set>

int main() {
    int n, temp, minValue = INT32_MAX;
    std::cin >> n;
    std::set<int> mySet;
    mySet.insert(0);
    int *results = new int[n];
    std::pair<std::set<int>::iterator, bool> it;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        it = mySet.insert(temp);
        if (it.second != 0) {
            if (it.first == mySet.begin()) {
                minValue = std::min(minValue, *it.first ^ *std::next(it.first));
            } else if (it.first == std::prev(mySet.end())) {
                minValue = std::min(minValue, *it.first ^ *std::prev(it.first));
            } else
                minValue = std::min(minValue,
                                    std::min(*std::prev(it.first) ^ *it.first, *it.first ^ *std::next(it.first)));
        }
        results[i] = minValue;
    }
    for (int i = 0; i < n; i++) {
        std::cout << results[i] << std::endl;
    }
    delete[] results;
}
