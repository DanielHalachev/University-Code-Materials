https://www.hackerrank.com/contests/sda-hw-9-2021/challenges/1-126-1

#include <iostream>
#include <set>
#include <map>
#include <unordered_map>

int main() {
    int n;
    std::cin >> n;
    int *a = new int[n];
    int *b = new int[n];
    int counter = 0;
    // store keys and how many of them we have
    std::unordered_map<int, int> keys;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        // search for existence of key
        const std::unordered_map<int, int>::iterator &iterator1 = keys.find(a[i]);
        // if key already exists, increase its quantity
        if (iterator1 != keys.end()) {
            iterator1->second++;
        }
            // otherwise, put it with quantity 1
        else {
            keys.insert({a[i], 1});
        }
        // search if the door has a key
        const std::unordered_map<int, int>::iterator &iterator2 = keys.find(b[i]);
        // if not - increase the broken doors
        if (iterator2 == keys.end()) {
            counter++;
        }
            // if there is a key for the door
        else {
            // if it's the last one, remove the key from the list of keys
            if (iterator2->second <= 1) {
                keys.erase(b[i]);
            }
                // if there are more keys than 1, remove one of them
            else {
                iterator2->second--;
            }
        }
    }
    std::cout << counter;
    delete[]a;
    delete[]b;
    return 0;
}
