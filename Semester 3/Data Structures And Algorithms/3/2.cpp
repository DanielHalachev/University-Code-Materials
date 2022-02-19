https://www.hackerrank.com/contests/sda-hw-3/challenges/challenge-3074

#include <iostream>

void merge(int arr[], int left, int middle, int right) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;
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

int search(int arr[], int n, int x) {
    if (x <= arr[0]) {
        return arr[0];
    }
    if (arr[n - 1] <= x) {
        return arr[n - 1];
    }
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x) {
            return arr[mid];
        }
        if (arr[mid] < x) {
            l = mid + 1;
        }
        if (arr[mid] > x) {
            r = mid - 1;
        }
    }
    int difference1 = x - arr[l - 1];
    int difference2 = arr[l] - x;
    return (difference1 <= difference2) ? arr[l - 1] : arr[l];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    int *topics = new int[n];
    int *teams = new int[m];
    for (int i = 0; i < n; i++) {
        std::cin >> topics[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> teams[i];
    }
    mergeSort(topics, 0, n - 1);
    for (int i = 0; i < m; i++) {
        std::cout << search(topics, n, teams[i]) << std::endl;
    }
    delete[] topics;
    delete[] teams;
}
