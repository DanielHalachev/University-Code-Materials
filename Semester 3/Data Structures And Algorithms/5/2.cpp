https://www.hackerrank.com/contests/sda-hw-5/challenges/bridge-battle-1

#include <iostream>
#include <queue>
#include <list>

int main() {
    int n;
    bool troopHasPassed = false;
    std::cin >> n;
    int *arr = new int[n];
    // input nums
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    int i = 0;
    // do until the end of the sequence
    std::list<int> positives;
    std::queue<int> negatives;
    while (i < n) {
        // collect the subsequence of positive numbers and the following subsequence of negative numbers
        while (arr[i] > 0 && i < n) {
            positives.push_back(arr[i]);
            i++;
        }
        while (arr[i] < 0 && i < n) {
            negatives.push(arr[i]);
            i++;
        }
        // fight
        while (!positives.empty() && positives.back() >= 0 && !negatives.empty()) {
            if (positives.back() > abs(negatives.front())) {
                negatives.pop();
            } else if (positives.back() == abs(negatives.front())) {
                negatives.pop();
                positives.pop_back();
            } else if (positives.back() < abs(negatives.front())) {
                positives.pop_back();
            }
        }
        if (positives.empty() && !negatives.empty()) {
            while (!negatives.empty()) {
//                positives.push_back(negatives.front());
                std::cout << negatives.front() << " ";
                negatives.pop();
            }
        }
    }
    // print the survivors
    if (positives.empty()) {
        while (!negatives.empty()) {
            std::cout << negatives.front() << " ";
            negatives.pop();
            troopHasPassed = true;
        }
    } else if (negatives.empty()) {
        while (!positives.empty()) {
            std::cout << positives.front() << " ";
            positives.pop_front();
            troopHasPassed = true;
        }
    }
    // in case nothing has been printed (no one has passed the bridge)
    if (!troopHasPassed) {
        std::cout << "\n";
    }
    delete[] arr;
}
