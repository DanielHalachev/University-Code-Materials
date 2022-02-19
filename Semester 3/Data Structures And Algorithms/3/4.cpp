https://www.hackerrank.com/contests/sda-hw-3/challenges/queries-5

#include <iostream>
#include <algorithm>

#define WIDTH 5

int search(const int *arr, int n, int x) {
    if (arr[0] > x) {
        return -1;
    }
    if (arr[n - 1] <= x) {
        return n - 1;
    }
    int left = 0, middle, right = n - 1;
    while (left <= right) {
        middle = (left + right) / 2;
        if (arr[middle] > x) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    return left - 1;
}

int numberOfElements(const int *numbers, int upperBoundIndex, int maxSum) {
    int numberOfElements = 0, sum = 0;
    // cycle in groups of WIDTH
    for (int i = upperBoundIndex; i >= 0; i -= WIDTH) {
        // in case you can't, then iterate
        if (i < WIDTH) {
            int j = i;
            while (j > -1) {
                sum += numbers[j];
                if (sum > maxSum) {
                    break;
                }
                numberOfElements++;
                j--;
            }
            break;
        }
        // in case you can:
        // then add the elements to the sum
        // for (int j = 0; j < WIDTH; j++) {
        //     sum += numbers[i - j];
        //     numberOfElements++;
        // }
        sum += numbers[i] + numbers[i - 1] + numbers[i - 2] + numbers[i - 3] + numbers[i - 4];
        numberOfElements += WIDTH;
        // if they are too much, subtract until good
        int j = i - WIDTH + 1;
        if (sum > maxSum) {
            while (j <= i) {
                sum -= numbers[j];
                numberOfElements--;
                if (sum <= maxSum) {
                    break;
                }
                j++;
            }
            break;
        }
    }
    // end this looping and return an answer
    return numberOfElements;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    int q;
    std::cin >> n >> q;
    int *numbers = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }
    auto queries = new std::pair<int, int>[q];
    int maxSums, maxValues;
    for (int i = 0; i < q; i++) {
        std::cin >> maxSums >> maxValues;
        queries[i].first = maxSums;
        queries[i].second = maxValues;
    }
    std::sort(numbers, numbers + n);
    for (int i = 0; i < q; i++) {
        int upperBoundIndex = search(numbers, n, queries[i].second);
        int maxSum = queries[i].first;
        printf("%i\n", numberOfElements(numbers, upperBoundIndex, maxSum));
    }
    delete[] numbers;
    delete[] queries;
}
