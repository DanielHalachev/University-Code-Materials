//https://www.hackerrank.com/contests/sda-hw-2/challenges/challenge-3091

#include <algorithm>
#include <iostream>

void merge(int arr[], int left, int middle, int right) {
    size_t leftSize = middle - left + 1;
    size_t rightSize = right - middle;
    // create temp arrays
    int *leftArray = new int[leftSize];
    int *rightArray = new int[rightSize];
    // copy the data to the temp arrays
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = arr[middle + i + 1];
    }
    int leftIndex = 0, rightIndex = 0;
    int indexOfMergedArray = left;
    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (leftArray[leftIndex] <= rightArray[rightIndex]) {
            arr[indexOfMergedArray] = leftArray[leftIndex];
            leftIndex++;
        } else {
            arr[indexOfMergedArray] = rightArray[rightIndex];
            rightIndex++;
        }
        indexOfMergedArray++;
    }
    // copy the rest of the left array if something's missing
    while (leftIndex < leftSize) {
        arr[indexOfMergedArray] = leftArray[leftIndex];
        leftIndex++;
        indexOfMergedArray++;
    }
    // copy the rest of the right array if something's missing
    while (rightIndex < rightSize) {
        arr[indexOfMergedArray] = rightArray[rightIndex];
        rightIndex++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int arr[], int left, int right) {
    int middle = left + (right - left) / 2;
    if (left < right) {
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

long scrooge(int presents[], int n, int k) {
    mergeSort(presents, 0, n-1);
    long minimalExpenses = 0;
    for (int i = 0; i < k; i++) {
        minimalExpenses += presents[i];
    }
    return minimalExpenses;
}

int main() {
    int n = 0;
    std::cin >> n;
    int k = 0;
    int *presents = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> presents[i];
    }
    std::cin >> k;
    std::cout << scrooge(presents, n, k);
    delete[] presents;
}
