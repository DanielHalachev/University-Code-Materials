https://www.hackerrank.com/contests/sda-hw-5/challenges/challenge-2695

#include <iostream>
#include <queue>


int findLowest(const int *arr, int left, int right) {
    int min = arr[left];
    for (int i = left + 1; i <= right; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    int n, d;
    std::cin >> n >> d;
    int *arr = new int[n];
    long temp = INT16_MAX;
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
        if (i < d && arr[i] < temp) {
            temp = arr[i];
        }
    }
    long sum = 0;
    for (int i = 0; i < n - d; i++) {
        sum += temp;
        if (arr[i + d] < temp) {
            temp = arr[i + d];
        } else if (arr[i] == temp) {
            temp = findLowest(arr, i + 1, i + d);
        }
    }
    sum += temp;
    std::cout << sum;
    delete[] arr;
    return 0;
}
