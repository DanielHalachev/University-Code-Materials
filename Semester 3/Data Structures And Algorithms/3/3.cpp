https://www.hackerrank.com/contests/sda-hw-3/challenges/doom

#include <algorithm>
#include <iostream>
#include <vector>

int binarySearch(const double *arr, int left, int right, double x) {
    while (right - left > 1) {
        int middle = left + (right - left) / 2;
        if (arr[middle] >= x)
            right = middle;
        else
            left = middle;
    }
    return right;
}

int LongestIncreasingSubsequenceLength(double *arr, int size) {
    if (size == 0) {
        return 0;
    }
    auto *tail = new double[size];
    for (int i = 0; i < size; i++) {
        tail[i] = 0;
    }
    int length = 1;
    tail[0] = arr[0];
    for (size_t i = 1; i < size; i++) {
        // assign the new smallest value if found
        if (arr[i] < tail[0]) {
            tail[0] = arr[i];
        }
            // continue to fill tail with the good stuff
        else if (arr[i] > tail[length - 1]) {
            tail[length++] = arr[i];
        }
            // arr[i] should have the LIS
        else {
            tail[binarySearch(tail, -1, length - 1, arr[i])] = arr[i];
        }
    }
    delete[] tail;
    return length;
}

int main() {
    int n = 0;
    std::cin >> n;
    auto *arr = new std::pair<double, double>[n];
    double input1, input2;
    for (int i = 0; i < n; i++) {
        std::cin >> input1 >> input2;
        arr[i] = std::pair<double, double>(input1, input2);
    }
    std::sort(arr, arr + n);
    auto *defences = new double[n];
    auto *attacks = new double[n];
    for (int i = 0; i < n; i++) {
        defences[i] = arr[i].first;
        attacks[i] = arr[i].second;
    }
    int lengthDefence = LongestIncreasingSubsequenceLength(defences, n);
    int lengthAttack = LongestIncreasingSubsequenceLength(attacks, n);
    std::cout << std::min(lengthDefence, lengthAttack);
    delete[] arr;
    delete[] defences;
    delete[] attacks;
}
